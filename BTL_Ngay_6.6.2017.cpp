//// Thi?t k? c�c ch? exit, chua c� ch? exit
////Thi?t k? c�c get,set
#include"Assignment.h"


int main() {
	account *temp=new account();
	temp->setUsername("tay142");
	account *thuthu=new account();
	thuthu->setUsername("thuthutest");

  	send_announcement_to_individual(thuthu,"3"); 
  	  	send_announcement_to_individual(thuthu,"3"); 
  	send_announcement_to_individual(thuthu,"3"); 
  	send_announcement_to_individual(thuthu,"3"); 

  	 	read_announcement(temp); 

	return 0;
}
