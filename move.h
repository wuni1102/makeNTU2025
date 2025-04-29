class Move{
    const int R_1A;
    const int R_1B;
    const int L_1A;
    const int L_1B;
    const double DPS; //cm, distance per second
    const double R; //cm, radiaus of rotation
public:
    Move(int R_1A, int R_1B, int L_1A, int L_1B, double DPS, double R):
     R_1A(R_1A), R_1B(R_1B), L_1A(L_1A), L_1B(L_1B), DPS(DPS), R(R) {} 
    void setPin();
    void forward(double dist);
    void backward(double dist);
    void turn_left(int angle);
    void turn_right(int angle);
};