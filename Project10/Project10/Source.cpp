#include "Header.h"
#include "Game.h"
#include "Singleton.h"
#include "Menu.h"



int main() {
	//����� ��������� �������� ����������
	Singleton* tm = &Singleton::instance();
	WelcomeScene scene{};
	scene.eventLoop();
	return 0;
}




