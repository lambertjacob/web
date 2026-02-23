#pragma once
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>


template <typename clock_chosen = std::chrono::steady_clock> 
class TokenBucket{
private:
   int m_rate;
   int m_burst;
   double m_tokens;
   typename clock_chosen::time_point m_last_refill;

   void refill(){
        auto now = clock_chosen::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_refill).count();
        double new_tokens = (elapsed / 1000.0) * m_rate;

        if(new_tokens > 0){
            //will never send a partial burst. so min of burst size or avail tokens. 
            m_tokens = std::min(static_cast<double>(m_burst), m_tokens + static_cast<int>(new_tokens));
            m_last_refill = now;
        }

        std::cout << "  tokens -> " << m_tokens << "\n";
    }

public:
    TokenBucket(const int rate, const int max_burst) : m_rate(rate), m_burst(max_burst), m_tokens(max_burst), m_last_refill(clock_chosen::now()) {}

    bool checkBucket(const int num_tokens){
       refill();

       if(m_tokens < num_tokens) return false;
       m_tokens -= num_tokens;
       return true;
    }

};