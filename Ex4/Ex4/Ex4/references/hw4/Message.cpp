#include <iostream>
#include "Message.H"

//*********************************************************************************************************
//* function name:	Message	
//* Description  :	Constructor of Message class
//* Parameters   :	source-the source of the message
//*				 :	subject-the subject of the message
//*			     :	content-the content of the message
//* Return Value :	None
//*********************************************************************************************************
Message::Message(string source, string subject, string content) : source_(source), subject_(subject), content_(content), read_(false) {}

//*********************************************************************************************************
//* function name:	Display	
//* Description  :	prints the message
//* Parameters   :	num- number of messages
//* Return Value :	None
//*********************************************************************************************************
void Message::Display(int num) const
{
	cout << num << ") "<< (read_ ? "" : "(Unread) ") << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
}

//*********************************************************************************************************
//* function name:	Read
//* Description  :	Read a Message
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void Message::Read()
{
    read_ = true;
	cout << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
	cout << "Content: " << content_ << endl;
}

//*********************************************************************************************************
//* function name: isRead
//* Description  : checks if this is a read message	
//* Parameters   : None
//* Return Value : Bool	
//*********************************************************************************************************
bool Message::isRead()
{
	return read_;
}

//*********************************************************************************************************
//* function name: MessageBox	
//* Description  : Constructor of MessageBox class	, sets values of 0 to all messages and those who not were read 
//* Parameters   : None
//* Return Value : None
//*********************************************************************************************************
MessageBox::MessageBox() : MessageBox_(MESSAGE), Total_Message_(0), Unread_Message_(0) {};

//*********************************************************************************************************
//* function name:	~MessageBox()
//* Description  :	Destructor of MessageBox class
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
MessageBox::~MessageBox() {
	MessageBox_.goHead();
	while (static_cast<Message*>(MessageBox_.getValue()) != NULL) {
		delete (static_cast<Message*>(MessageBox_.getValue()));
		MessageBox_.getNext();
	}
}

//*********************************************************************************************************
//* function name: Add	
//* Description  : add a new massage the massagebox
//* Parameters   : newMessage - new message	
//* Return Value : None	
//*********************************************************************************************************
void MessageBox::Add(Message newMessage) {
	MessageBox_.add(new Message(newMessage));
	Total_Message_++;
	Unread_Message_++;
}

//*********************************************************************************************************
//* function name:	Size
//* Description  :	Return the number of total messages
//* Parameters   :	None
//* Return Value :	Total_Message_-the number of them 
//*********************************************************************************************************
int MessageBox::Size(){
	return Total_Message_;
}

//*********************************************************************************************************
//* function name:	UnreadSize
//* Description  :	Return the number of total unread messages
//* Parameters   :	None
//* Return Value :	Unread_Message_-the number of them
//*********************************************************************************************************
int MessageBox::UnreadSize(){
	return Unread_Message_;
}

//*********************************************************************************************************
//* function name: Print	
//* Description  : Display a summary of all messages	
//* Parameters   : None	
//* Return Value : None	
//*********************************************************************************************************
void MessageBox::Print() {
	MessageBox_.goHead();
	int n = MessageBox_.getSize();
	for (int i = 0; i<n; i++){
		Message* tmp = static_cast<Message*>(MessageBox_.getValue());
		tmp->Display(i+1);
		MessageBox_.getNext();
	}
}

//*********************************************************************************************************
//* function name: ReadMessage	
//* Description  : use it to read a message
//* Parameters   : read a message and also update the number of the unread mesaages	
//* Return Value : Result- if we succeded return SUCCESS else FAILURE
//*********************************************************************************************************
Result MessageBox::ReadMessage(int messageNum) {
	int n = MessageBox_.getSize();
	if (messageNum <= 0 || messageNum > n) return FAILURE;
	MessageBox_.goHead();
	for (int i=0;i<messageNum-1;i++)
		MessageBox_.getNext(); // go to the desired message
	Message* tmp = static_cast<Message*>(MessageBox_.getValue());
	if (tmp->isRead() == false) Unread_Message_--;
	tmp->Read();
	return SUCCESS;
}