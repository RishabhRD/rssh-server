class Stream{
  public:
    virtual int read() = 0;
    virtual const int write(const char* buffer, int size) = 0;
};
