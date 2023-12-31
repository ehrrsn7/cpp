//
//  score.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#pragma once

#include <iostream>
#include <string>

#include "../../ui/uiDraw.hpp"
#include "../../vector/point.hpp"

class Score {

private:
    int score;
    Point position;

public:
    Score() {
        std::cout << "Score constructor called." << std::endl;
        score = 0;
    }
    
    void set(Point p) { position.set(p); }
    
    void display() {
        std::string scoreText = "Score: ";
        scoreText += std::to_string(score);
        drawText(position, scoreText.c_str());
    }
    
    void add(int dPoints) { score += dPoints; }    
    void reset() { score = 0; }
};
