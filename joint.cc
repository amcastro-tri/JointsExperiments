
template<class T>
class Context {
public:  
};

template<typename T>
class JointInt {
public:
  virtual T GetTransform(Context<T>& ctx) = 0;
};

class Joint: public JointInt<int>, JointInt<double> {  
};

template<typename T>
class RevoluteJointInt: public JointInt<T> {
  T GetTransform(Context<T>& ctx) {
    return T();
  }
};

class RevoluteJoint: public RevoluteJointInt<int>, RevoluteJointInt<double> {  
};

int main()
{
  Joint* j = (Joint*)(new RevoluteJoint());
  
  return 0;
}
