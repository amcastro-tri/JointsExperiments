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
class RevoluteJoint: public Joint {
public:
  RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
    pimpl_int_.reset(new  RevoluteJointImplementation<int>());
    pimpl_double_.reset(new  RevoluteJointImplementation<double>());
  }

  ~RevoluteJoint() {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  int GetTransform(Context<int>& ctx) {
    cout << __PRETTY_FUNCTION__ << endl;
    return pimpl_int_->GetTransform(ctx);
  }
  double GetTransform(Context<double>& ctx) {
    cout << __PRETTY_FUNCTION__ << endl;
    return pimpl_double_->GetTransform(ctx);
  }

private:
  std::unique_ptr<RevoluteJointImplementation<int>> pimpl_int_;
  std::unique_ptr<RevoluteJointImplementation<double>> pimpl_double_;
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
