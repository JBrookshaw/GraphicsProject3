// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "p1controls.hpp"

glm::mat4 P1CARD1;
glm::mat4 P1CARD2;
glm::mat4 P1CARD3;

glm::mat4 P2CARD1;
glm::mat4 P2CARD2;
glm::mat4 P2CARD3;

glm::mat4 P1CARD1Copy;
glm::mat4 P1CARD2Copy;
glm::mat4 P1CARD3Copy;

glm::mat4 P2CARD1Copy;
glm::mat4 P2CARD2Copy;
glm::mat4 P2CARD3Copy;

glm::mat4 myScalingMatrix = glm::scale(2.3f, 1.0f , 3.5f);

glm::mat4 myScalingMatrix2 = glm::scale(0.8f, 1.0f ,0.8f);
glm::mat4 myScalingMatrix3 = glm::scale(0.95f, 1.0f ,0.95f);

glm::mat4 myMatrix = glm::translate(0.0f, 0.0f, -0.05f);
glm::mat4 select = glm::translate(0.0f, 0.005f, 0.0f);

glm::mat4 selectedCard = glm::translate(0.0f, 1.5f, 0.0f);

mat4 rotation = mat4(
	vec4( cos(3.14), 0.0,  sin(3.14),  0.0),
	vec4(0.0,  1.0, 0.0, 0.0),
	vec4(-sin(3.14), 0.0,  cos(3.14),  0.0),
	vec4( 0.0, 0.0, 0.0, 1.0)
	);

mat4 rotation2 = mat4(
	vec4( cos(0.2), 0.0,  sin(0.2),  0.0),
	vec4(0.0,  1.0, 0.0, 0.0),
	vec4(-sin(0.2), 0.0,  cos(0.2),  0.0),
	vec4( 0.0, 0.0, 0.0, 1.0)
	);

mat4 dieAnimation = myScalingMatrix3*rotation2;

//false = player1 | true = player2
int moves = 0;
int player2 = 20;
bool turn = false;
bool p1attacking = false;

float myDistance = 60, myDistance2 =60, myDistance3 = 60, myDistance4 = 60;

bool attackright = false, attackleft = false, attackmiddle = false, attackplayer = false;
bool die = false, die2 = false, die3 = false, die4 = false;
bool p1card1selected = false, p1card2selected = false, p1card3selected  = false;
bool p1card1selectedanimation = false, p1card2selectedanimation = false, p1card3selectedanimation  = false;



bool p2card3dead1 = false; //Tex2
bool p2card2dead1 = false; //Tex6
bool p2card1dead1 = false; //Tex3




int p1Moves() {

	return moves;
}

void p1Zero() {

	moves = 0;
}

void p2Loss(int loss2) {

	player2 = player2 - loss2;

}

void p2LifeSet(int set2) {

	player2 = set2;

}

int p2Life() {

	return player2;

}






void resetDeadFlags(){
p2card3dead1 = false; //Tex2
p2card2dead1 = false; //Tex6
p2card1dead1 = false; //Tex3

}

bool getP2Card3Dead(){
	return p2card3dead1;
}
bool getP2Card2Dead(){
	return p2card2dead1;
}
bool getP2Card1Dead(){
	return p2card1dead1;
}

void setP2Card3Dead(){
	p2card3dead1 = false;
}
void setP2Card2Dead(){
	p2card2dead1 = false;
}
void setP2Card1Dead(){
	p2card1dead1 = false;
}



void player1Inputs(){

	readInputs();

	player1Selection();

	if(p1card1selected){
		p1card1attack();
	}
	else if(p1card3selected)
	{
		p1card3attack();
	}
		else if(p1card2selected)
	{
		p1card2attack();
	}

}

void p1card1attack(){

	if(!attackright && attackleft && !attackmiddle && !attackplayer){
		P1CARD1 = glm::translate(P1CARD1, glm::vec3(0.0f, 0.0f, -0.08f));
		myDistance--;
		if(myDistance <= 0){
			P1CARD1 = P1CARD1Copy;
			attackleft = false;
			myDistance = 60;
			die=true;
		}
	}
	if(die){
		P2CARD3 = P2CARD3 * dieAnimation;
		myDistance--;
		if(myDistance <= 0){
			//P2CARD3 = P2CARD3Copy;
			p2card3dead1 = true;
			die = false;
			myDistance=60;
			p1card1selectedanimation = false;
			p1card1selected =false;
			p1attacking = false;
			moves++;
		}
	}
	if(attackright && !attackleft && !attackmiddle && !attackplayer){
		P1CARD1 = glm::translate(P1CARD1, glm::vec3(0.12f, 0.0f, -0.08f));
		myDistance2--;
		if(myDistance2 <= 0){
			P1CARD1 = P1CARD1Copy;
			attackright = false;
			myDistance2 = 60;
			die2=true;
		}
	}
	if(die2){
		P2CARD1 = P2CARD1 * dieAnimation;
		myDistance2--;
		if(myDistance2 <= 0){
			p2card1dead1 = true;//P2CARD1 = P2CARD1Copy;
			die2 = false;
			myDistance2=60;
			 p1card1selectedanimation = false;
			p1card1selected =false;
			p1attacking = false;
			moves++;
			
		}
	}

	if(!attackright && !attackleft && attackmiddle && !attackplayer){
		P1CARD1 = glm::translate(P1CARD1, glm::vec3(0.06f, 0.0f, -0.08f));
		myDistance3--;
		if(myDistance3 <= 0){
			P1CARD1 = P1CARD1Copy;
			attackmiddle = false;
			myDistance3 = 60;
			die3=true;
		}
	}
	if(die3){
		P2CARD2 = P2CARD2 * dieAnimation;
		myDistance3--;
		if(myDistance3 <= 0){
			p2card2dead1 = true;//P2CARD2 = P2CARD2Copy;
			die3 = false;
			myDistance3=60;
			 p1card1selectedanimation = false;
			p1card1selected =false;
			p1attacking = false;
			moves++;
			
		}
	}
	if(!attackright && !attackleft && !attackmiddle && attackplayer){
		P1CARD1 = glm::translate(P1CARD1, glm::vec3(0.06f, 0.0f, -0.19f)); // NEEDS TO BE ADJUSTED TO MIDDLE BACK
		myDistance4--;
		if(myDistance4 <= 0){
			P1CARD1 = P1CARD1Copy;			
			attackplayer = false;
			myDistance4 = 60;
			die4=true;
		}
	}

	if(die4){
		//P2CARD2 = P2CARD2 * dieAnimation;			// THIS NEEDS TO BE OPPOSITE PLAYER
		myDistance4--;
		if(myDistance4 <= 0){
			p2Loss(2);			//Lose 2 Life, can be more.
			die4 = false;
			myDistance4=60;
			 p1card1selectedanimation = false;
			p1card1selected =false;
			p1attacking = false;
			moves++;
			
		}
	}
	
}

void p1card2attack(){

	if(!attackright && !attackleft && attackmiddle && !attackplayer){
		P1CARD2 = glm::translate(P1CARD2, glm::vec3(0.0f, 0.0f, -0.06f));
		myDistance--;
		if(myDistance <= 0){
			P1CARD2 = P1CARD2Copy;
			attackmiddle = false;
			myDistance = 60;
			die=true;
		}
	}
	if(die){
		P2CARD2 = P2CARD2 * dieAnimation;
		myDistance--;
		if(myDistance <= 0){
			p2card2dead1 = true;//P2CARD2 = P2CARD2Copy;
			die = false;
			myDistance=60;
			p1card2selectedanimation = false;
			p1card2selected =false;
			p1attacking = false;
			moves++;
		}
	}
	if(attackright && !attackleft && !attackmiddle && !attackplayer){
		P1CARD2 = glm::translate(P1CARD2, glm::vec3(0.06f, 0.0f, -0.06f));
		myDistance2--;
		if(myDistance2 <= 0){
			P1CARD2 = P1CARD2Copy;
			attackright = false;
			myDistance2 = 60;
			die2=true;
		}
	}
	if(die2){
		P2CARD1 = P2CARD1 * dieAnimation;
		myDistance2--;
		if(myDistance2 <= 0){
			p2card1dead1 = true;//P2CARD1 = P2CARD1Copy;
			die2 = false;
			myDistance2=60;
			 p1card2selectedanimation = false;
			p1card2selected =false;
			p1attacking = false;
			moves++;
			
		}
	}

	if(!attackright && attackleft && !attackmiddle && !attackplayer){
		P1CARD2 = glm::translate(P1CARD2, glm::vec3(-0.06f, 0.0f, -0.06f));
		myDistance3--;
		if(myDistance3 <= 0){
			P1CARD2 = P1CARD2Copy;
			attackleft = false;
			myDistance3 = 60;
			die3=true;
		}
	}
	if(die3){
		P2CARD3 = P2CARD3 * dieAnimation;
		myDistance3--;
		if(myDistance3 <= 0){
			p2card3dead1 = true;//P2CARD3 = P2CARD3Copy;
			die3 = false;
			myDistance3=60;
			p1card2selectedanimation = false;
			p1card2selected =false;
			p1attacking = false;
			moves++;
			
		}
	}
	if(!attackright && !attackleft && !attackmiddle && attackplayer){
		P1CARD2 = glm::translate(P1CARD2, glm::vec3(0.0f, 0.0f, -0.19f)); // NEEDS TO BE ADJUSTED TO MIDDLE BACK
		myDistance4--;
		if(myDistance4 <= 0){
			P1CARD2 = P1CARD2Copy;			
			attackplayer = false;
			myDistance4 = 60;
			die4=true;
		}
	}

	if(die4){
		//P2CARD2 = P2CARD2 * dieAnimation;			// THIS NEEDS TO BE OPPOSITE PLAYER
		myDistance4--;
		if(myDistance4 <= 0){
			p2Loss(2);		//Lose two life, can be more
			die4 = false;
			myDistance4=60;
			 p1card2selectedanimation = false;
			p1card2selected =false;
			p1attacking = false;
			moves++;
			
		}
	}
	
}

void p1card3attack(){

	if(attackright && !attackleft && !attackmiddle && !attackplayer){
		P1CARD3 = glm::translate(P1CARD3, glm::vec3(0.0f, 0.0f, -0.08f));
		myDistance--;
		if(myDistance <= 0){
			P1CARD3 = P1CARD3Copy;
			attackright = false;
			myDistance = 60;
			die=true;
		}
	}
	if(die){
		P2CARD1 = P2CARD1 * dieAnimation;
		myDistance--;
		if(myDistance <= 0){
			p2card1dead1 = true;//P2CARD1 = P2CARD1Copy;
			die = false;
			myDistance=60;
			 p1card3selectedanimation = false;
			p1card3selected =false;
			p1attacking = false;
			moves++;
		}
	}
	if(!attackright && attackleft && !attackmiddle && !attackplayer){
		P1CARD3 = glm::translate(P1CARD3, glm::vec3(-0.12f, 0.0f, -0.08f));
		myDistance2--;
		if(myDistance2 <= 0){
			P1CARD3 = P1CARD3Copy;
			attackleft = false;
			myDistance2 = 60;
			die2=true;
		}
	}
	if(die2){
		P2CARD3 = P2CARD3 * dieAnimation;
		myDistance2--;
		if(myDistance2 <= 0){
			p2card3dead1 = true;//P2CARD3 = P2CARD3Copy;
			die2 = false;
			myDistance2=60;
			 p1card3selectedanimation = false;
			p1card3selected =false;
			p1attacking = false;
			moves++;
		}
	}

	if(!attackright && !attackleft && attackmiddle && !attackplayer){
		P1CARD3 = glm::translate(P1CARD3, glm::vec3(-0.06f, 0.0f, -0.08f));
		myDistance3--;
		if(myDistance3 <= 0){
			P1CARD3 = P1CARD3Copy;
			attackmiddle = false;
			myDistance3 = 60;
			die3=true;

		}
	}
	if(die3){
		P2CARD2 = P2CARD2 * dieAnimation;
		myDistance3--;
		if(myDistance3 <= 0){
			p2card2dead1 = true;//P2CARD2 = P2CARD2Copy;
			die3 = false;
			myDistance3=60;
			 p1card3selectedanimation = false;
			p1card3selected =false;
			p1attacking = false;
			moves++;
		}
	}
	if(!attackright && !attackleft && !attackmiddle && attackplayer){
		P1CARD3 = glm::translate(P1CARD3, glm::vec3(-0.06f, 0.0f, -0.19f)); // NEEDS TO BE ADJUSTED TO MIDDLE BACK
		myDistance4--;
		if(myDistance4 <= 0){
			P1CARD3 = P1CARD3Copy;			
			attackplayer = false;
			myDistance4 = 60;
			die4=true;
		}
	}

	if(die4){
		//P2CARD2 = P2CARD2 * dieAnimation;			// Life Subtraction
		myDistance4--;
		if(myDistance4 <= 0){
			p2Loss(2);		//Life Subtraction
			die4 = false;
			myDistance4=60;
			 p1card3selectedanimation = false;
			p1card3selected =false;
			p1attacking = false;
			moves++;
		}
	}

}

void player1Selection(){
	if(!p1card1selectedanimation && p1card1selected)
	{
		P1CARD1 = P1CARD1 * selectedCard;
		p1card1selectedanimation=true;
		p1card2selectedanimation=false;
		p1card3selectedanimation=false;

		p1card2selected = false;
		p1card3selected = false;
		P1CARD2 = P1CARD2Copy;
		P1CARD3 = P1CARD3Copy;
	}
	if(!p1card2selectedanimation && p1card2selected)
	{
		P1CARD2 = P1CARD2 * selectedCard;

		p1card1selectedanimation=false;
		p1card2selectedanimation=true;
		p1card3selectedanimation=false;

		p1card1selected = false;
		p1card3selected = false;
		P1CARD1 = P1CARD1Copy;
		P1CARD3 = P1CARD3Copy;
	}
	if(!p1card3selectedanimation && p1card3selected)
	{

		P1CARD3 = P1CARD3 * selectedCard;

		p1card1selectedanimation=false;
		p1card2selectedanimation=false;
		p1card3selectedanimation=true;

		p1card1selected = false;
		p1card2selected = false;

		P1CARD2 = P1CARD2Copy;
		P1CARD1 = P1CARD1Copy;
	}
}

void createCopys(){
	P1CARD1Copy = P1CARD1;
	P1CARD2Copy = P1CARD2;
	P1CARD3Copy = P1CARD3;

	P2CARD1Copy = P2CARD1;
	P2CARD2Copy = P2CARD2;
	P2CARD3Copy = P2CARD3;
}

void readInputs(){

	bool isCardSelected = p1card1selected || p1card2selected || p1card3selected;
	if(!p1attacking) {
		if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS && isCardSelected){
			attackright = true;
			attackleft=false;
			attackmiddle =false;
			attackplayer = false;
			p1attacking = true;
				
		}
		else	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS && isCardSelected){
			attackright = false;
			attackleft=true;
			attackmiddle =false;
			attackplayer = false;
			p1attacking = true;
				
		}
		else	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS && isCardSelected){
			attackright = false;
			attackleft=false;
			attackmiddle =true;
			attackplayer = false;
			p1attacking = true;
				
		}
			else	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS && isCardSelected){
			attackright = false;
			attackleft=false;
			attackmiddle =false;
			attackplayer = true;
			p1attacking = true;
				
		}



	if (glfwGetKey( window, GLFW_KEY_1 ) == GLFW_PRESS){
		p1card1selected = true;
		//p1card1selectedanimation = true;
	}
	else	if (glfwGetKey( window, GLFW_KEY_2 ) == GLFW_PRESS){
		p1card2selected = true;
		//p1card2selectedanimation = true;
	}
	else	if (glfwGetKey( window, GLFW_KEY_3 ) == GLFW_PRESS){
		p1card3selected = true;
		//p1card3selectedanimation = true;
	}
		}//end if attacking
}

glm::mat4 getP1Card1(){
	return P1CARD1;
}
glm::mat4 getP1Card2(){
	return P1CARD2;
}
glm::mat4 getP1Card3(){
	return P1CARD3;
}
glm::mat4 getP2Card1(){
	return P2CARD1;
}
glm::mat4 getP2Card2(){
	return P2CARD2;
}
glm::mat4 getP2Card3(){
	return P2CARD3;
}

glm::mat4 getP1Card1C(){
	return P1CARD1Copy;
}
glm::mat4 getP1Card2C(){
	return P1CARD2Copy;
}
glm::mat4 getP1Card3C(){
	return P1CARD3Copy;
}
glm::mat4 getP2Card1C(){
	return P2CARD1Copy;
}
glm::mat4 getP2Card2C(){
	return P2CARD2Copy;
}
glm::mat4 getP2Card3C(){
	return P2CARD3Copy;
}

void  setP1Card1(glm::mat4 model){
	P1CARD1 = model;
}
void  setP1Card2(glm::mat4 model){
	P1CARD2 = model;
}
void  setP1Card3(glm::mat4 model){
	P1CARD3 = model;
}
void  setP2Card1(glm::mat4 model){
	P2CARD1 = model;
}
void  setP2Card2(glm::mat4 model){
	P2CARD2 = model;
}
void  setP2Card3(glm::mat4 model){
	P2CARD3 = model;
}