class s_block{
    
};

class snake{
    private:
        s_block body[MAX_BODY];
        s_block* head;
        int length;
        int direction;
        int velocity;
    public:
        bool turn(int direction);
        bool is_alive();

};
