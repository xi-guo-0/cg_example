#include "mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

Mesh::Mesh(const std::string &filename) {
    std::ifstream ifs(filename);
    if (ifs.fail()) {
        return;
    }
    std::string line;
    while (!ifs.eof()) {
        std::getline(ifs, line);
        std::istringstream iss(line);
        std::string classification;
        iss >> classification;
        if ("v" == classification) {
            Eigen::Vector3d v;
            iss >> v.x() >> v.y() >> v.z();
            verts.push_back(v);
        } else if ("vn" == classification) {
            Eigen::Vector3d n;
            iss >> n.x() >> n.y() >> n.z();
            norms.push_back(n.normalized());
        } else if ("vt" == classification) {
            Eigen::Vector2d uv;
            iss >> uv.x() >> uv.y();
            tex_coord.push_back(uv);
        } else if ("f" == classification) {
            int f;
            int cnt = 0;
            while (iss >> f) {
                facet_vrt.push_back(f - 1);
                ++cnt;
            }
            if (3 != cnt) {
                std::cerr
                        << "Error: the obj file is supposed to be triangulated"
                        << std::endl;
                ifs.close();
                return;
            }
        }
    }
}

int Mesh::nverts() const {
    return verts.size();
}

int Mesh::nfaces() const {
    return facet_vrt.size() / 3;
}

Eigen::Vector3d Mesh::normal(const int iface, const int nthvert) const {
    return norms[facet_nrm[iface * 3 + nthvert]];
}

Eigen::Vector3d Mesh::vert(const int i) const {
    return verts[i];
}

Eigen::Vector3d Mesh::vert(const int iface, const int nthvert) const {
    return verts[facet_vrt[iface * 3 + nthvert]];
}

Eigen::Vector2d Mesh::uv(const int iface, const int nthvert) const {
    return tex_coord[facet_tex[iface * 3 + nthvert]];
}
