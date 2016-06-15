#include<iostream>
#include<memory>
#include<vector>
using namespace std;

template<class T>
class Context {
public:  
};

// Interface for a single type
template<typename T>
class JointInterface {
public:
  virtual T GetTransform(Context<T>& ctx) = 0;
};

#define JOINT_IMPORT_IMPLEMENTATIONS(DerivedJoint, T)             \
  T GetTransform(Context<T>& ctx) override {                      \
    cout << __PRETTY_FUNCTION__ << endl;                          \
    return DerivedJoint##Implementation<T>::GetTransform(ctx);    \
  }

// Interface for multiple types
class Joint: public JointInterface<int>, JointInterface<double> {
public:
  virtual ~Joint() {}
};

// Implementation for a single type
template<typename T>
class RevoluteJointImplementation: public JointInterface<T> {
public:
  RevoluteJointImplementation() {
    cout << __PRETTY_FUNCTION__ << endl;
  }
  ~RevoluteJointImplementation() {
    cout << __PRETTY_FUNCTION__ << endl;
  }
  
  T GetTransform(Context<T>& ctx) override {
    cout << __PRETTY_FUNCTION__ << endl;
    return T();
  }
};

// Implementation for multiple types
class RevoluteJoint: public Joint, RevoluteJointImplementation<int>, RevoluteJointImplementation<double> {
public:
  RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  ~RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  JOINT_IMPORT_IMPLEMENTATIONS(RevoluteJoint, int);
  JOINT_IMPORT_IMPLEMENTATIONS(RevoluteJoint, double);
};



int main()
{
  RevoluteJoint* j = new RevoluteJoint();

  std::vector<std::unique_ptr<Joint>> joints_owner;
  joints_owner.push_back(std::unique_ptr<Joint>(j));

  Context<double> cd;
  Context<int> ci;

  j->GetTransform(cd);
  j->GetTransform(ci);
  
  return 0;
}
