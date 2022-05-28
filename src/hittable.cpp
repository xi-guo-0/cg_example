#include <hittable.h>

#include <utility>

HitElement::HitElement(std::shared_ptr<Material> material)
    : material_(std::move(material)) {
}

std::shared_ptr<Material> HitElement::GetMaterial() const {
    return material_;
}

Sphere::Sphere(Eigen::Vector3d center, double radius,
               std::shared_ptr<Material> material)
    : center_(std::move(center)), radius_(radius),
      HitElement(std::move(material)) {
}

const Eigen::Vector3d &Sphere::GetCenter() const {
    return center_;
}

double Sphere::GetRadius() const {
    return radius_;
}


bool Sphere::Hit(const Ray &ray, double t0, double t1, HitRecord *hrec) const {
    auto oc = ray.origin_ - GetCenter();
    auto a = ray.direction_.dot(ray.direction_);
    auto b = 2.0 * ray.direction_.dot(oc);
    auto c = oc.dot(oc) - GetRadius() * GetRadius();
    double delta = b * b - 4 * a * c;
    if (delta < 0.0) {
        return false;
    }
    auto root = (-b - sqrt(delta)) / a / 2.0;
    if (root < t0 || t1 <= root) {
        root = (-b + sqrt(delta)) / a / 2.0;
        if (root < t0 || t1 <= root) {
            return false;
        }
    }
    hrec->t_ = root;
    hrec->point_ = ray.At(hrec->t_);
    auto outward_normal = (hrec->point_ - GetCenter()).normalized();
    hrec->SetFaceNormal(ray, outward_normal);
    hrec->material_ = material_;
    return true;
}

Triangle::Triangle(Eigen::Vector3d a, Eigen::Vector3d b, Eigen::Vector3d c,
                   std::shared_ptr<Material> material)
    : a_(std::move(a)), b_(std::move(b)), c_(std::move(c)),
      HitElement(std::move(material)) {
}

const Eigen::Vector3d &Triangle::a() const {
    return a_;
}

const Eigen::Vector3d &Triangle::b() const {
    return b_;
}

const Eigen::Vector3d &Triangle::c() const {
    return c_;
}

bool Triangle::Hit(const Ray &ray, double t0, double t1,
                   HitRecord *hrec) const {
    Eigen::Matrix3d A;
    A.col(0) = a() - b();
    A.col(1) = a() - c();
    A.col(2) = ray.direction_;
    Eigen::Vector3d B = a() - ray.origin_;
    Eigen::Vector3d X = A.colPivHouseholderQr().solve(B);
    auto beta = X(0);
    auto gamma = X(1);
    auto t = X(2);
    if (!(t0 <= t && t < t1)) {
        return false;
    }
    if (!(0 <= gamma && gamma <= 1)) {
        return false;
    }
    if (!(0 <= beta && beta <= 1 - gamma)) {
        return false;
    }
    hrec->t_ = t;
    hrec->point_ = ray.At(hrec->t_);
    auto outward_normal =
            ((c() - a()).cross(b() - a())).normalized();
    hrec->SetFaceNormal(ray, outward_normal);
    hrec->material_ = material_;
    return true;
}
void HitList::add(std::shared_ptr<Hittable> &hittable) {
    hit_list_.push_back(hittable);
}
bool HitList::Hit(const Ray &ray, double t0, double t1, HitRecord *hrec) const {
    HitRecord temp_rec;
    auto hit_anything = false;
    auto closest_so_far = t1;
    for (const auto &hittable: hit_list_) {
        if (hittable->Hit(ray, t0, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t_;
        }
    }
    *hrec = temp_rec;
    return hit_anything;
}
