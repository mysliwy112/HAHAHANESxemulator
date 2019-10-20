#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H

#include<vector>

using namespace std;

class RealController
{
    public:
        RealController();
        virtual ~RealController();
        vector<sf::Keyboard::Key> keycodes;
        vector<int> getPresses();
        void setKeycodes(vector<sf::Keyboard::Key> keys);

    protected:

    private:
};

#endif // REALCONTROLLER_H
