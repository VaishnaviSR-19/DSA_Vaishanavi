// /*Write a program to create Hospital class. Mention Patient name, patient id, medicine list and total 
// bill as member variables in a class. Write a function to display the bill. While displaying the bill 
// show medicine purchased and price of medicine and show total bill of that patient. Write a 
// constructor and destructor inside the program. Create the two object dynamically and perform the 
// operations. Assume data whenever required.*/
// //Vaishnavi Rajmane
// //2061
// //S.Y CSE
// //S4
// #include<iostream>
// using namespace std;

// class hospital
// {
//   private:
//   string Patient_name;
//   int 	Patient_id;
//   string medicine_list;
//   int total_bill;
  
//   public:
//   	hospital(string name,int id,string medicine,int bill) 
//   		{
//   			Patient_name = name;
//   			Patient_id = id;
//   			medicine_list = medicine;
//   			total_bill = bill;
//   			cout<<"In constructor"<<endl;
//   		}
  
//   	void display()
//   		{
//   			cout<<"Patient_name:"<<Patient_name<<endl;
//   			cout<<"Patient_id:"<<Patient_id<<endl;
//   			cout<<"medicine_list:"<<medicine_list <<endl;
//   			cout<<"total_bill:"<<total_bill<<endl;
//   		}
  		
//   	~hospital()
//   		{
//   			cout<<"In destructor";
// 	    }
// };

// int main()
// {
// 	hospital *p1=new hospital("Vaishnavi Rajmane",2061,"paracetamol,botox,captopril",500);
// 	hospital *p2=new hospital("Vijay Rajmane",2710,"paracetamol,botox,captopril",500);
	
// 	p1->display();
// 	p2->display();
	
// 	return 0;
// }