#include<iostream>
#include<memory>
#include<vector>
using namespace std;

template<class T>
class Context {
public:  
};

#define JOINT_BASE_INTERFACE(Method, T, ReturnT)	\
  virtual ReturnT GetTransform(Context<T>& ctx) = 0;

#define JOINT_BASE_INTERFACES()	                        \
  JOINT_BASE_INTERFACE(GetTransform, int, int);		\
  JOINT_BASE_INTERFACE(GetTransform, double, double);

// Interface for a single type
template<typename T>
class JointInterface {
public:
  virtual T GetTransform(Context<T>& ctx) = 0;
};

// Interface for multiple types
class Joint /*: public JointInterface<int>, JointInterface<double> {*/ { //Multiple inheritanc cause compiler error with CRTP
public:
  Joint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }
  virtual ~Joint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  JOINT_BASE_INTERFACES();
};

#define JOINT_BASE_IMPLEMENTATION(Method, T, ReturnT)	\
  ReturnT GetTransform(Context<T>& ctx) override {	\
    cout << __PRETTY_FUNCTION__ << endl;                \
    return derived_->GetTransform(ctx);                 \
  }

#define JOINT_BASE_IMPLEMENTATIONS()                        \
  JOINT_BASE_IMPLEMENTATION(GetTransform, double, double);  \
  JOINT_BASE_IMPLEMENTATION(GetTransform, int, int);        

// CRTP (Curiously recurring template pattern) base joint class
template<class Derived>
class JointBase: public Joint {
public:
  JointBase(Derived* derived): derived_(derived) {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  virtual ~JointBase() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  JOINT_BASE_IMPLEMENTATIONS();
private:
  Derived* derived_;
};

// Implementation for multiple types
class RevoluteJoint: public JointBase<RevoluteJoint> {
public:
  RevoluteJoint(): JointBase(this) {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  ~RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  template<typename T>
  T GetTransform(Context<T>& ctx) {
    cout << __PRETTY_FUNCTION__ << endl;
    return T();
  }
};

int main()
{
  Joint* j = new RevoluteJoint();  

  std::vector<std::unique_ptr<Joint>> joints_owner;

  joints_owner.push_back(std::unique_ptr<Joint>(j));

  Context<double> cd;
  Context<int> ci;

  for(std::unique_ptr<Joint>& j: joints_owner) {
    std::cout << std::endl;
    j->GetTransform(cd);
    std::cout << std::endl;
    j->GetTransform(ci);
  }

  std::cout << std::endl;

  return 0;
}
