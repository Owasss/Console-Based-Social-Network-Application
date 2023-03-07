#include<iostream>
#include<string>
#include<fstream>

using namespace std;
class user;
class post;
class comments;
class Pages;

class object
{
protected:
	string ID;
	string name;
public:
	void print()
	{
		cout << ID << "-" << name << endl;
	}
	string getName()
	{
		return name;
	}
	string getID()
	{
	    return ID;
	}
	
};


class user :public object
{
private:
	user** friends;
	Pages** pages_liked;
	int size_pages ;
	int size_frnds ;
public:
	user()
	{
		friends = nullptr;
		pages_liked = nullptr;
		size_pages = 0;
		size_frnds = 0;
	}
	user** getFriends()
	{
		return friends;
	}
	Pages** get_likedpages()
	{
		return pages_liked;
	}
	int getTotalLikedPages()
	{
		return size_pages;
	}
	int getTotalFriends()
	{
		return size_frnds;
	}
	string getID()
	{
		return ID;
	}
	string getName()
	{
		return name;
	}
	void setId_Name(string Id, string Fname, string Lname)
	{
		ID = Id;
		name = Fname + " " + Lname;
	}
	void setfriends(user* f)
	{
		if (size_frnds == 10)
		{
			cout << "Limit reached!\n";
			return;
		}

		if (friends != nullptr)
		{
			user** temp;
			temp = new user * [size_frnds + 1];
			for (int i = 0; i < size_frnds; i++)
				temp[i] = friends[i];
			delete[]friends;
			friends = temp;
		}
		else
		{
			friends = new user * [1];
		}
		friends[size_frnds] = f;
		size_frnds++;
	}

	user operator =(user& obj)
	{
		ID = obj.ID;
		name = obj.name;
	}
	void setPages(Pages* p)
	{

		if (size_pages == 10)
		{
			cout << "Limit reached!\n";
			return;
		}

		if (pages_liked != nullptr)
		{
			Pages** temp;
			temp = new Pages * [size_pages + 1];
			for (int i = 0; i < size_pages; i++)
				temp[i] = pages_liked[i];
			delete[]pages_liked;
			pages_liked = temp;
		}
		else
		{
			pages_liked = new Pages * [1];
		}
		pages_liked[size_pages] = p;
		size_pages++;
	}
	~user()
	{
		delete [] pages_liked;
		delete [] friends;
	}
	friend ostream& operator << (ostream& out, const user& obj);
};
ostream& operator << (ostream& out, const user& obj)
{
	out << obj.ID << "\t" << obj.name << endl;
	return out;
}

class comments
{
	string commentID;
	string comm;
	object* postedby;
public:
	comments()
	{
		commentID = "";
		postedby = nullptr;
		comm = "";
	}
	object* get_postedby()
	{
		return postedby;
	}
	string get_comment()
	{
		return comm;
	}
	comments(string id, string c, object* obj)
	{
		commentID = id;
		postedby = obj;
		comm = c;
	}
	void setInitials(string id, string c, object* obj)
	{
		commentID = id;
		postedby = obj;
		comm = c;
	}
	~comments()
	{
		postedby = nullptr;
	}
};
class date
{
private:
	int day;
	int month;
	int year;

public:

	date()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	date(int d, int m, int y)
	{
		this->day = d;
		this->month = m;
		this->year = y;
	}

	date(date const &d)
	{

		day=d.day;
		month=d.month;
		year=d.year;

	}
	date operator-(int y)
	{
		int x;
		x=day-y;

		return date(x,month,year);
	}
	void set_day(int d)
	{
		this->day = d;
	}

	int get_day()
	{
		return day;
	}
	bool operator==(const date&obj)
	{
		if (obj.day==day && obj.month==month && year==obj.year)
			return true;
		return false;
	}
	void set_month(int m)
	{
		this->month = m;
	}

	int get_month()
	{
		return month;
	}

	void set_year(int y)
	{
		this->year = y;
	}

	int get_year()
	{
		return year;
	}
	friend ostream& operator << (ostream& out, const date& obj);
};
ostream& operator << (ostream& out, const date& obj)
{
	out << obj.day << "/" << obj.month << "/" << obj.year ;
	return out;
}

class post
{
	string postid;
	object** likedby;
	comments* cmnt;
	int likeCount;
	int commentCount;
protected:
	string postText;
	object* sharedby;
	date Date;
public:
	
    virtual void display()
    {
        cout<<sharedby->getName()<<" shared "<<""<<postText<<"";
        cout<<"......("<<Date<<")\n";
    }
	virtual void disp()
	{
		cout<<sharedby->getName()<<" shared "<<""<<postText<<""<<endl;
		print_cmnts();
	}
	void print_cmnts()
	{
		for(int i=0;i<commentCount;i++)
		{
			cout<<"\t\t"<<cmnt[i].get_postedby()->getName() <<" wrote: '"<<cmnt[i].get_comment()<<"'\n";
		}
	}
	comments* getComment()
	{
		return cmnt;
	}
	post()
	{
		commentCount = 0;
		likeCount = 0;
		postid = "";
		postText = "";
		cmnt = new comments[10];
		likedby = nullptr;
	}
	post(string pId, date date_, string postText_)
	{
		commentCount = 0;
		likeCount = 0;
		postid = pId;
		Date = date_;
		postText = postText_;
		cmnt = new comments[10];
		likedby = nullptr;
	}
	date getDate()
	{
		return Date;
	}
	string getID()
	{
		return postid;
	}
	void setInitials(string pId, date date_, string postText_)
	{
		postid = pId;
		Date = date_;
		postText = postText;
	}
	void set_sharedby(object* obj)
	{
		sharedby = obj;
	}
	void addLike(object* u)
	{
		if (likeCount <= 10)
		{
			if (likedby != nullptr)
			{
				object** temp;
				temp = new object * [likeCount + 1];
				for (int i = 0; i < likeCount; i++)
					temp[i] = likedby[i];
				delete[]likedby;
				likedby = temp;
			}
			else
			{
				likedby = new object * [1];
			}
			likedby[likeCount] = u;
			likeCount++;
			
		}
		else
			cout << "YOU EXCEED THE LIKES LIMIT!!" << endl;
	}
	post(const post& obj)
	{
	    this->commentCount = obj.commentCount;
		likeCount = obj.likeCount;
		postid = obj.postid;
		Date = obj.Date;
		postText = obj.postText;
		cmnt=new comments[10];
		for(int i=0;i<commentCount;i++)
		     cmnt[i]=obj.cmnt[i];
		 likedby=obj.likedby;
		sharedby=obj.sharedby;
	}
    post& operator=(const post& obj)
    {
        this->commentCount = obj.commentCount;
		likeCount = obj.likeCount;
		postid = obj.postid;
		Date = obj.Date;
		postText = obj.postText;
		for(int i=0;i<commentCount;i++)
		     cmnt[i]=obj.cmnt[i];
		
		     likedby=obj.likedby;
		sharedby=obj.sharedby;
			return *this;
    }
	void addComments(string id, string c, object* pby)
	{
		if (commentCount <= 10)
		{
			cmnt[commentCount].setInitials(id, c, pby);
			commentCount++;
		}
		else
			cout << "YOU EXCEED THE COMMENTS LIMIT!!" << endl;
	}
	void displayLikes()
	{
		for (int i = 0;i < likeCount;i++)
		{
			likedby[i]->print();
		}
	}
    object* getSharedby()
    {
        return sharedby;
    }
	string gettxt()
	{
		return postText;
	}
	~post()
	{
		delete [] likedby;
		delete [] cmnt;
		sharedby = nullptr;
 	}
};
class Pages :public object
{
	int people_count;
	post* posts;
	int postCount;
public:
	Pages()
	{
		people_count = 0;
		ID = "";
		posts = nullptr;
		postCount=0;
	}
	void setPageId_title(string pId, string Title)
	{
		ID = pId;
		name = Title;
	}
	post* get_post()
	{
		return posts;
	}
   	void setPosts(post p)
	{
		if (posts != nullptr)
		{
			post* temp;
			temp = new post[postCount + 1];
			for (int i = 0; i < postCount; i++)
				temp[i] = posts[i];
			delete[]posts;
			posts = temp;
		}
		else
		{
			posts = new post[1];
		}
		posts[postCount] = p;
		postCount++;
	}

	friend ostream& operator << (ostream& out, const Pages& obj);
	string getID()
	{
		return ID;
	}
	void dispPost()
	{
		cout << name<<" ";
		for (int i = 0; i < postCount; i++)
		{
			posts[i].disp();
		}
	}
	~Pages()
	{
		delete [] posts;
	}
};
ostream& operator << (ostream& out, const Pages& obj)
{
	out << obj.ID << "-" << obj.name << endl;
	return out;
}

class Activity :public post
{
	string type;
	string value;
public:
	void set_type(int t) 
	{
		if (t == 1)
			type = "feeling";
		else if (t == 2)
			type = "feeling about";
		else if (t == 3)
			type = "making";
		else if (t == 4)
			type = "celebrating";
		else
		{
			type = "";
			cout << "INVALID TYPE!!" << endl;
		}
	}

	string get_type()
	{
		return type;
	}
	Activity() :post()
	{
		type = "";
		value = "";
	}

	void set_value(string s)
	{
		value = s;
	}
	string get_value() 
	{
		return value;
	}

	Activity(string id, date d, string t, int type_, string value_) :post(id, d, t) 
	{
		set_type(type_);
		value = value_;
	}

	void disp()
	{
		cout<<sharedby->getName()<<" is "<<type<<" "<<value<<endl<<postText<<endl;
		print_cmnts();
	}

	void display()
	{
	     cout<<sharedby->getName()<<" is "<<type<<" "<<value<<endl<<postText;
	     cout<<"......("<<Date<<")\n";
	}

	friend ostream& operator<<(ostream& out, const Activity& obj);
};

ostream& operator<<(ostream& out, const Activity& obj)
{
	out << "is " << obj.type << " a " << obj.value << endl;
	return out;
}

class app
{
	date curDate;
	user* us;
	Pages* pgs;
	int total_pages;
	user* users;
	int total_users;
	post** Posts;
	int total_posts;
	int total_comments;

public:
	app()
	{
		us = nullptr;
		pgs = nullptr;
		users = nullptr;
		Posts = nullptr;
		total_pages = 0;
		total_posts = 0;
		total_users = 0;
		total_comments = 0;
	}

	void readAllFiles()
	{
		ifstream pages("SocialNetworkPages.txt");
		if (pages.is_open())
		{
			pages >> total_pages;
			pgs = new Pages[total_pages];
			for (int i = 0;i < total_pages;i++)
			{
				string id, t;
				pages >> id;
				pages.ignore();
				getline(pages, t);
				pgs[i].setPageId_title(id, t);
			}
			pages.close();
		}
		else
		{
			cout << "Unable to read 'SocialNetworkPages.txt'!\n";
		}
		ifstream User("SocialNetworkUsers.txt");
		if (User.is_open())
		{
			User >> total_users;
			users = new user[total_users];
			for (int i = 0;i < total_users;i++)
			{
				string id, fn, ln, t;
				User >> id;
				User >> fn;
				User >> ln;
				getline(User, t);
				users[i].setId_Name(id, fn, ln);
			}
			User.seekg(0, ios::beg);
			int temp;
			User >> temp;
			for (int i = 0;i < total_users;i++)
			{
				string temp, frnd, pg_liked;
				User >> temp;
				User >> temp;
				User >> temp;
				while (frnd != "-1")
				{
					User >> frnd;
					if (frnd == "-1")
						break;
					for (int j = 0;j < total_users;j++)
					{
						if (frnd == users[j].getID())
						{
							users[i].setfriends(&users[j]);
							break;
						}
					}
				}
				while (pg_liked != "-1")
				{
					User >> pg_liked;
					if (pg_liked == "-1")
						break;
					for (int j = 0;j < total_pages;j++)
					{
						if (pg_liked == pgs[j].getID())
						{
							users[i].setPages(&pgs[j]);
							break;
						}
					}
				}
			}
			User.close();
		}
		else
		{
			cout << "Unable to read 'SocialNetworkUsers.txt'!\n";
		}
		ifstream post_file("SocialNetworkPosts.txt");
		if (post_file.is_open())
		{
		  
			string junk;
			post_file >> total_posts;
			post_file.ignore();
			getline(post_file, junk);
			Posts = new post * [total_posts];
			for (int i = 0;i < total_posts;i++)
			{
				string id, txt, f;
				int d, m, y;
				int a;
				post_file >> id;
	
				post_file >> d >> m >> y;
				post_file.ignore();
				getline(post_file, txt);
				post_file >> a;
				date Date(d,m,y);
				if (a != 0)
				{
				    post_file.ignore();
					getline(post_file, f);
					Posts[i] = new Activity(id, Date, txt, a, f);
				}
				else
				{
					Posts[i] = new post(id, Date, txt);
				}
				string sby;
				post_file >> sby;
				for (int j = 0;j < total_users;j++)
				{
					if (sby == users[j].getID())
					{
						Posts[i]->set_sharedby(&users[j]);
						break;
					}
				}
				
				for (int j = 0;j < total_pages;j++)
				{
					if (sby == pgs[j].getID())
					{
						Posts[i]->set_sharedby(&pgs[j]);
						
						break;
					}
				}
				string lby;
				while (lby != "-1")
				{
					post_file >> lby;
					if (lby == "-1")
						break;
					for (int j = 0;j < total_users;j++)
					{
						if (lby == users[j].getID())
						{
							Posts[i]->addLike(&users[j]);
							break;
						}
					}
					for (int j = 0;j < total_pages;j++)
					{
						if (lby == pgs[j].getID())
						{
							Posts[i]->addLike(&pgs[j]);
							break;
						}
					}
				}
				post_file.ignore();
				getline(post_file, junk);
			
			}
			post_file.close();
		}
		else
		{
			cout << "Unable to read 'SocialNetworkPosts.txt'!\n";
		}
		ifstream commment_file("SocialNetworkComments.txt");

		object* pby = nullptr;
		if (commment_file.is_open())
		{
			commment_file >> total_comments;

			for (int i = 0;i < total_comments;i++)
			{
				string id, pid, oid, txt;
				commment_file >> id;
				commment_file >> pid;
				for (int j = 0;j < total_posts;j++)
				{
					if (pid == Posts[j]->getID())
					{
						commment_file >> oid;
						for (int j = 0;j < total_users;j++)
						{
							if (oid == users[j].getID())
							{
								pby = &users[j];
								break;
							}
						}
						for (int j = 0;j < total_pages;j++)
						{
							if (oid == pgs[j].getID())
							{
								pby = &pgs[j];
								break;
							}
						}
						commment_file.ignore();
						getline(commment_file, txt);
						Posts[j]->addComments(id, txt, pby);
						break;
					}
				}

			}
			commment_file.close();
		}
		else
		{
			cout << "Unable to read 'SocialNetworkComments.txt'!\n";
		}
	}
	void search(string tosearch)
	{
	    cout<<"--------------------------------------------------------------------------\n";
	    cout<<"                    Search result of '"<<tosearch<<"'\n";
	    cout<<"--------------------------------------------------------------------------\n\n";
		bool u=false;
		for (int i=0;i<total_users;i++)
		{
			if(users[i].getName().find(tosearch,0)!=string::npos)
			{
				if(!u)
					cout<<"Users: \n";
				object* ok=&users[i];
				cout<<"---";
				ok->print();
				cout<<endl;
				u=true;
			}
		}
		u=false;
		for (int i=0;i<total_pages;i++)
		{
			if(pgs[i].getName().find(tosearch,0)!=string::npos)
			{
				if(!u)
					cout<<"Pages: \n";
				object* ok=&pgs[i];
				cout<<"---";
				ok->print();
				cout<<endl;
				u=true;
			}
		}
		u=false;
		for (int i=0;i<total_posts;i++)
		{
			if(Posts[i]->gettxt().find(tosearch,0)!=string::npos)
			{
				if(!u)
					cout<<"Posts: \n";
				cout<<"---";
				Posts[i]->display();
				cout<<endl;
				u=true;
			}
		}
	}

	void InputUser(string uid)
	{
		bool found = false;
		for (int i = 0;i < total_users;i++)
		{
			if (uid == users[i].getID())
			{
				us = &users[i];
				found = true;
				cout << users[i].getName() << " set as current user!\n";
				break;
			}
		}
		if (!found)
		{
			cout << "No such user found.Re-enter!\n";
		}
	}

	void setDate(int d,int m,int y)
	{
		date day(d,m,y);
		curDate = day;
		cout << "System date: "<<curDate<<endl;
	}

    void viewapost(string postid)
	{
	    cout<<"\n"<<postid<<endl;
		for(int i=0;i<total_posts;i++)
		{
			if(postid==Posts[i]->getID())
			{
			    
				Posts[i]->display();
				Posts[i]->print_cmnts();
			}
		}
	}
	void viewHome()
	{
	    cout<<endl<<us->getName()<<"-Home\n";
	    for(int k=0;k<total_posts;k++)
	    {
	       if(Posts[k]->getDate()==curDate ||Posts[k]->getDate()==curDate-1) {
	          for(int j=0;j<us->getTotalFriends();j++) 
	          {
	              if(Posts[k]->getSharedby()==us->getFriends()[j] )
	                 {
	                     cout<<"---";
	                     Posts[k]->disp();
	                     cout<<endl;
	                 }
	          }
	          for(int j=0;j<us->getTotalLikedPages();j++) 
	          {
	              if(Posts[k]->getSharedby()==us->get_likedpages()[j] )
	               {
	                   cout<<"---";
	                   Posts[k]->disp();
	                   cout<<endl;
	               }
	          }
	       }
	   }
		    
	}

	void likeapost(string pid)
	{
		bool liked=false;
		for (int j = 0;j < total_posts;j++)
		{
			if (pid == Posts[j]->getID())
			{
				Posts[j]->addLike(us);
				cout<<"\n\n"<<us->getName()<<" liked "<<pid<<endl<<endl;
				liked = true;
				break;
			}
		}
		if (!liked)
		{
			cout << "No such post found!\n";
		}
	}
	void viewlikedlist(string pid)
	{
	    cout<<"\nPost Likes-"<<pid<<"\n";
		bool shown = false;
		for (int j = 0;j < total_posts;j++)
		{
			if (pid == Posts[j]->getID())
			{
				Posts[j]->displayLikes();
				shown = true;
				break;
			}
		}
		
		if (!shown)
		{
			cout << "No such post found!\n";
		}
	}
	void addComment(string pid, string txt)
	{
		bool added = false;
		for (int j = 0;j < total_posts;j++)
		{
			if (pid == Posts[j]->getID())
			{
				string id = "c" + to_string(total_comments + 1);
				Posts[j]->addComments(id, txt, us);
				cout<<"\n\nComment added to "<<pid<<endl<<endl;
				total_comments++;
				added = true;
				break;
			}
		}
		if (!added)
		{
			cout << "No such post found!\n";
		}
	}
	void showfriends()
	{
        cout<<endl<<us->getName()<<"-Friend list\n";
        for(int i=0;i<us->getTotalFriends();i++)
        {
            object* temp=((us->getFriends())[i]);
            temp->print();
        }
	
	}
    
    void showlikedpgs()
    {
        cout<<endl<<us->getName()<<"-Liked pages\n";
        for(int i=0;i<us->getTotalLikedPages();i++)
        {
            object* temp=((us->get_likedpages())[i]);
            temp->print();
        }
    }
    void viewTimeline()
    {
        cout<<endl<<us->getName()<<"-Timeline\n";
	    for(int i=0;i<total_posts;i++)
	    {
	        if(Posts[i]->getSharedby()==us)
	        {
	            cout<<"---";
	            Posts[i]->display();
	            Posts[i]->print_cmnts();
	            cout<<endl;
	        }
	    }
    }
	void viewPage(string pgid)
	{
	    Pages* pg_selected;
	    for(int j=0;j<total_pages;j++)
	    {
	         if(pgs[j].getID()==pgid)
	         {
	             pg_selected=&pgs[j];
	             cout<<endl<<pgs[j].getName()<<endl;
	             break;
	         }
	    }
	    for(int i=0;i<total_posts;i++)
	    {
	        if(Posts[i]->getSharedby()==pg_selected)
	        {
	            cout<<"---";
	            Posts[i]->display();
	            Posts[i]->print_cmnts();
	        }
	    }
	}
		~app()
	{
		delete [] us;
		delete [] pgs;
		delete [] users;
		for(int i =0 ; i<total_posts; i++)
			delete [] Posts[i];
		delete [] Posts;
		cout<<"App destructor called"<<endl;
	}
};
int main()
{
	app ap;
	ap.readAllFiles();
	ap.InputUser("u7");
	ap.setDate(27,07,2021);
	ap.showfriends();
	ap.showlikedpgs();
	ap.viewHome();
	ap.viewTimeline();
	ap.viewlikedlist("post5");
	ap.likeapost("post5");
	ap.viewlikedlist("post5");
	ap.viewapost("post4");
	ap.addComment("post8","Thanks for the wishes");
	ap.viewapost("post8");
	ap.viewPage("p1");
	//ap.search("Birthday");
	ap.search("Ali");

	system("pause");
	return 0;
}