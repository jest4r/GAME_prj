#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const int TARGET_DELTATIME = 1.5f;

class Timer
{
    public:
        inline float GetDeltatime(){return m_deltatime;}
        inline static Timer* GetInstance() {return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer();}
        void Tick();
    private:
        Timer(){}
        static Timer* s_Instance;
        float m_deltatime;
        float m_lasttime;
};

#endif // TIMER_H
