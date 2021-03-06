#ifndef CONTROLS2_HPP
#define CONTROLS2_HPP

void player2Inputs();
void createCopys_();

void p2card1attack();
void p2card2attack();
void p2card3attack();

void p1Loss(int loss1);
void p1LifeSet(int set1);
int p1Life();

int p2Moves();
void p2Zero();

void readInputs_();
void player2Selection();

void rev2();

glm::mat4 getP1_Card1();
glm::mat4 getP1_Card2();
glm::mat4 getP1_Card3();
glm::mat4 getP2_Card1();
glm::mat4 getP2_Card2();
glm::mat4 getP2_Card3();

void setP1_Card1(glm::mat4 model);
void setP1_Card2(glm::mat4 model);
void setP1_Card3(glm::mat4 model);
void setP2_Card1(glm::mat4 model);
void setP2_Card2(glm::mat4 model);
void setP2_Card3(glm::mat4 model);

bool getP1Card3Dead();
bool getP1Card2Dead();
bool getP1Card1Dead();

void setP1Card1Dead();
void setP1Card2Dead();
void setP1Card3Dead();

void resetDeadFlags();

#endif