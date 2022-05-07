class GameObject{
    public:
        virtual void _display() = 0;
        virtual void _update() = 0;
        void update(){
            if (updateIndex <= 0){
                updateIndex = updateSpeed;
                _update();
            }
            else{
                updateIndex--;
            }
            _display();
        }

    private:
        const int updateSpeed = 3;
    protected:
        int updateIndex = 0;
};