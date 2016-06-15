#include<iostream>
#include<memory>
#include<vector>
using namespace std;

#define DRAKE_IMPORT_IMPLEMENTATION(Class, Method, T, ReturnT) \
  ReturnT Method(Context<T>& ctx) override {			  \
    cout << __PRETTY_FUNCTION__ << endl;                          \
    return Class##Implementation<T>::GetTransform(ctx);    \
  }

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
  DRAKE_IMPORT_IMPLEMENTATION(DerivedJoint, GetTransform, T, T);

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

#define REVOLUTE_JOINT_IMPORT_IMPLEMENTATIONS()        \
  JOINT_IMPORT_IMPLEMENTATIONS(RevoluteJoint, int);    \
  JOINT_IMPORT_IMPLEMENTATIONS(RevoluteJoint, double);

// Implementation for multiple types
class RevoluteJoint: public Joint, RevoluteJointImplementation<int>, RevoluteJointImplementation<double> {
public:
  RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  ~RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  REVOLUTE_JOINT_IMPORT_IMPLEMENTATIONS();

  /* This is what the macro above expands to:
  double GetTransform(Context<double>& ctx) override {
    RevoluteJointImplementation<double>::GetTransform(c);
  }

  int GetTransform(Context<int>& ctx) override {
    RevoluteJointImplementation<int>::GetTransform(c);
  }
  */
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
