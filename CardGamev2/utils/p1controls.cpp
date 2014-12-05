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
	  bool turn = false;

		float myDistance = 60;
		float myDistance2 = 60;
		bool check = false;
		bool check2 = false;
		bool die = false;
		bool die2 = false;

		bool p1card1selected = false;
		bool p1card2selected = false;
		bool p1card3selected = false;

		bool p1card1selectedanimation = false;
		bool p1card2selectedanimation = false;
		bool p1card3selectedanimation = false;

void player1Inputs(){
	
	readInputs();

	player1Selection();
	
	p1card3attack();

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

void p1cardattack(){
	if(check && ! check2){
			P1CARD3 = glm::translate(P1CARD3, glm::vec3(0.0f, 0.0f, -0.05f));
			myDistance--;
			if(myDistance <= 0){
				P1CARD3 = P1CARD3Copy;
				check = false;
				myDistance = 60;
				die=true;
			}
		}
		if(die){
			P2CARD1 = P2CARD1 * dieAnimation;
			myDistance--;
			if(myDistance <= 0){
				P2CARD1 = P2CARD1Copy;
				die = false;
				myDistance=60;
			}
		}
		if(check2 && !check){
			P1CARD3 = glm::translate(P1CARD3, glm::vec3(-0.12f, 0.0f, -0.05f));
			myDistance2--;
			if(myDistance2 <= 0){
				P1CARD3 = P1CARD3Copy;
				check2 = false;
				myDistance2 = 60;
				die2=true;
			}
		}
		if(die2){
			P2CARD3 = P2CARD3 * dieAnimation;
			myDistance2--;
			if(myDistance2 <= 0){
				P2CARD3 = P2CARD3Copy;
				die2 = false;
				myDistance2=60;
			}
		}

}

void p1card3attack(){
		
	if(check && ! check2){
			P1CARD3 = glm::translate(P1CARD3, glm::vec3(0.0f, 0.0f, -0.05f));
				P1CARD3 = glm::translate(P1CARD3, glm::vec3(0.0f, 0.005f, 0.0f));
			myDistance--;
			if(myDistance <= 0){
				P1CARD3 = P1CARD3Copy;
				check = false;
				myDistance = 60;
				die=true;
			}
		}
		if(die){
			P2CARD1 = P2CARD1 * dieAnimation;
			myDistance--;
			if(myDistance <= 0){
				P2CARD1 = P2CARD1Copy;
				die = false;
				myDistance=60;
			}
		}

		if(check2 && !check){
			P1CARD3 = glm::translate(P1CARD3, glm::vec3(-0.12f, 0.0f, -0.05f));
				P1CARD3 = glm::translate(P1CARD3, glm::vec3(0.0f, 0.005f, 0.0f));
			myDistance2--;
			if(myDistance2 <= 0){
				P1CARD3 = P1CARD3Copy;
				check2 = false;
				myDistance2 = 60;
				die2=true;
			}
		}
		if(die2){
			P2CARD3 = P2CARD3 * dieAnimation;
			myDistance2--;
			if(myDistance2 <= 0){
				P2CARD3 = P2CARD3Copy;
				die2 = false;
				myDistance2=60;
			}
		}

}

void readInputs(){

if(p1card3selected){
	
		if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		check = true;
	}
		else	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		check2 = true;
	}

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