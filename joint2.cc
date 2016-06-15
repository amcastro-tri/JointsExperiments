
template<class T>
class Context {
public:  
};

template<typename T>
class JointPolicy {
public:
  virtual T GetTransform(Context<T>& ctx) = 0;
};

class Joint {
public:
  virtual int GetTransform(Context<int>& ctx) = 0;
  virtual double GetTransform(Context<double>& ctx) = 0;
};

template<typename T>
class RevoluteJointImplementation: public JointPolicy<T> {
  T GetTransform(Context<T>& ctx) {
    return T();
  }
};

class RevoluteJoint: public RevoluteJointImplementation<int>, RevoluteJointImplementation<double> {
public:
};



int main()
{
  //Joint* j = new RevoluteJoint(); // This does not even compile
  
  return 0;
}
