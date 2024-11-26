#pragma once
#include <SFML/Audio.hpp>


using namespace sf;

class SetSound {
    public:
        SoundBuffer s1, s2, s3;
        Sound jump, bonus, fail;

        SetSound() {
            s1.loadFromFile("jump.ogg");
            s2.loadFromFile("bonus.ogg");
            s3.loadFromFile("fail.ogg");

            jump.setBuffer(s1);
            bonus.setBuffer(s2);
            fail.setBuffer(s3);
        }
};

SetSound sound;