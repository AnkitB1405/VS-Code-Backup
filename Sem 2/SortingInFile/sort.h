struct student
{
	int roll;
	char name[20];
};
void init_ptr(struct student s[], struct student *p[], int n);
void swap( struct student** lhs,  struct student** rhs);
void disp(struct student* p[], int n) ;
void selection_sort_roll_no(struct student* s[],int n);
void selection_sort_names(struct student* s[],int n);