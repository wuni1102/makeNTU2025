class Head{
    const int IN_1;
    const int IN_2;
    const int IN_3;
    const int IN_4;
    const int DT; // delay time as DT smaller, motor run faster
public:
    Head(int IN_1, int IN_2, int IN_3, int IN_4, int DT):
        IN_1(IN_1), IN_2(IN_2), IN_3(IN_3), IN_4(IN_4), DT(DT) {}
    void setPin();
    void forward(int angle);
    void backward(int angle);
    void test();
};