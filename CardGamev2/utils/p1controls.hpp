#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void player1Inputs();
void createCopys();

void p1card1attack();
void p1card2attack();
void p1card3attack();


void readInputs();
void player1Selection();

glm::mat4 getP1Card1();
glm::mat4 getP1Card2();
glm::mat4 getP1Card3();
glm::mat4 getP2Card1();
glm::mat4 getP2Card2();
glm::mat4 getP2Card3();

void setP1Card1(glm::mat4 model);
void setP1Card2(glm::mat4 model);
void setP1Card3(glm::mat4 model);
void setP2Card1(glm::mat4 model);
void setP2Card2(glm::mat4 model);
void setP2Card3(glm::mat4 model);

#endif