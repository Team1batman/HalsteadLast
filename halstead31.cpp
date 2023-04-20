#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include<cmath>
#include<dirent.h>
#include<ios> 
using namespace std;

//global values;

ofstream outfile;
ifstream operators_list;
int flowerL=0;
int flowerR=0;
int circleL=0;
int circleR=0;
int squareL=0;
int squareR=0;
int doubleQuo_counter=0;
int singleQuo_counter=0;
int n1=0,n2=0,N1=0,N2=0;

//increment left and right flower bracket count;
void checkFlowerBrackets(char ch)
{
	if(ch=='{')
		flowerL++;
	else
		flowerR++;
}

//increment left and right circular bracket count;
void checkCircleBrackets(char ch)
{
        if(ch=='(')
	circleL++;
	else
	circleR++;
}

//increament left and right square bracket count;
void checkSquareBrackets(char ch)
{
	if(ch=='[')
	squareL++;
	else
	squareR++;

}

// check the single and qouble quotations is it finds a pair it will push into operators set
//if already present increases N1++
int QuoCount(unordered_set<string> *operators,string word,int quo)
{
		if(operators->empty())
		{
			 operators->insert(word);
			 n1++;
			 N1++;
			 return 1;
		}
		else
		{
			if(operators->find(word)!=operators->end())
			{
				N1=N1 + quo;
				return 1;
			}
			else
			{
				operators->insert(word);
				n1++;
				N1++;
				if(quo>1)
					N1+=quo-1;	
				return 1;
			}
		}

		return 0;
}

//insertOper is only for operators it will check and insert the string into the operators set
//if already present , increases N1++;
int insertOperators(unordered_set<string> *operators,string word)
{

	if(operators->empty())
	{
		 operators->insert(word);
  		 n1++;
   		 N1++;
		 return 1;
     	}
      	else
       	{
        	if(operators->find(word)!=operators->end())
	 	{
	  		N1++;
			return 1;
	   	}	
	    	else
	     	{
	       		operators->insert(word);
	         	n1++;
		   	N1++;
			return 1;
		}
	}
	return 0;
}



//check function check for each string given to it wether it's a operator or operand  
int check(unordered_set<string> *keys, unordered_set<string> *operators,unordered_set<string> *operands,string oneword)
{
//cout<<"hey i'm inside check\n";
//cout<<oneword<<":one_word\n";
	if(keys->find(oneword)!=keys->end())
	{
		return insertOperators(operators,oneword);
	}
	else
	{
		if(oneword!="" && oneword!=" ")
	 	{
			if(operands->empty())
			{
				operands->insert(oneword);
				n2++;
				N2++;
				return 1;
			}
			else
			{
	 			if(operands->find(oneword) != operands->end())
				{
	        			N2++;
					return 1;
				}
				else
				{
				 //cout<<oneword<<"before inserting operator\n";

					operands->insert(oneword);
					n2++;
					N2++;
					return 1;
               		 	}
			}
		

         	}
		return 0;
	}

}

//all the not matched string are sent here to check them  char by char 
//depending it a number ,alphabet or symboles it will divide it and send to check; 
void notMatched(unordered_set<string> *keys,unordered_set<string> *operators,unordered_set<string> *operands,string sample)
{
	int ip=0;
	//cout<<sample<<" in function\n";
	string word=sample;
	int d=0;
	//cout<<word.length()<<":word length\n";
	for(unsigned int k=0;k<word.length();k++)
	{
		string oneword="";
		while(isalpha(word[k]))
		{
			if(k==word.length())
			     break;
			oneword+=word[k];
		//	cout<<oneword<<":word\n";
			k++;
		}
		//cout<<":out of alpha check\n";
		//cout<<d<<" :d\n";

		if(!oneword.empty())
		 d=check(keys,operators,operands,oneword);
		 //cout<<d<<":returned d\n";
		if(d==1)
		{
			k--;
			d=0;
			continue;
		}

		while(isdigit(word[k]))
		{
			if(k==word.length())
			    break;
			oneword+=word[k];
			//cout<<oneword<<":word\n";
			k++;
		}
		//cout<<"out of digit\n";
		 //cout<<d<<" :d\n";
		if(!oneword.empty())
		d=check(keys,operators,operands,oneword);
		//cout<<d<<":returned d\n";
		if(d==1)
		{
			k--;
			d=0;
			continue;
		}

		while(!(isalpha(word[k]) ^ isdigit(word[k])))
		{
			//	if(k==word.length())
			//		 break;
				if((word[k]=='{')||(word[k]=='}'))
				{
				//	cout<<word[k]<<":inside {} if\n";
					checkFlowerBrackets(word[k]);
					ip++;
					break;
				}
				if((word[k]=='(')|| (word[k]==')'))
				{
				//	cout<<word[k]<<":inside () if\n";

					checkCircleBrackets(word[k]);
					ip++;
					break;
				}
				if((word[k]=='[')||(word[k]==']'))
				{
				//	cout<<word[k]<<":inside [] if\n";
					checkSquareBrackets(word[k]);
					ip++;
					break;
				}
				if(word[k]=='"')
				{
				//	cout<<word[k]<<":inside \" if\n";

					doubleQuo_counter++;
					ip++;
					break;
				}
				if(word[k]=='\'')
				{
				//	cout<<word[k]<<":inside ' if\n";

					singleQuo_counter++;
					ip++;
					break;
				}

				if((k<word.length()-1) && (word[k]==word[k+1]))
				{

					string one="";
					one+=word[k];
					one+=word[k+1];
				//	cout<<one<<":inside {} if\n";
					check(keys,operators,operands,one);
					k++;
					ip++;
					break;
				}
				else
				{

					oneword+=word[k];
				//	cout<<word<<":word is\n";
				//	cout<<word.length()<<":length\n";
				//	cout<<k<<":k\n";
				//	cout<<oneword<<":word\n";

				}
			k++;

			if(k==word.length())
			break;

		}
		if(ip==1)
		{
		//	cout<<ip<<": ip\n";
			ip=0;
			continue;
		}

		//cout<<"out of either\n";
		// cout<<d<<" :d\n";
		// cout<<oneword<<" out side either\n";

		if(!oneword.empty())
		d=check(keys,operators,operands,oneword);

	//	cout<<d<<":returned d\n";
		if(d==1)
		{
			k--;
		//	cout<<"ater decrement\n";
			d=0;
			continue;
		}
	//	cout<<k<<" end of for\n";
	}

	if((doubleQuo_counter!=0)&&((doubleQuo_counter%2)==0))
	{
		int quo=doubleQuo_counter / 2;
		QuoCount(operators,"\"\"",quo);
		doubleQuo_counter=0;

	}

	if((singleQuo_counter!=0)&&((singleQuo_counter%2)==0))
	{
		int quo=singleQuo_counter / 2;
		QuoCount(operators,"''",quo);
		singleQuo_counter=0;
	}
	if((flowerL!=0)&&(flowerL==flowerR))
	{
		insertOperators(operators,"{}");
		flowerL=flowerR=0;
	}
	if((circleL!=0)&&(circleL==circleR))
	{
		 insertOperators(operators,"()");
		circleL=circleR=0;
	}
	if((squareL!=0)&&(squareL==squareR))
	{
		 insertOperators(operators,"[]");
		squareL=squareR=0;
	}

}

//take the whole progaram in to a cyclometric vector and given to cyclometricComplex
//it will check each line present in the vector and calculate the cyclometric complexity
double cyclometricComplex(vector<string> cyclometric)
{
	string file;
	int m,e,n,p,pi,s;
	m=e=n=p=pi=s=0;



//	for(unsigned int j=0;j<cyclometric.size();j++)
//	{
//		file+=cyclometric[j];
//
//	}
//	cout<<file<<endl;

	for(unsigned int i=0;i<cyclometric.size();i++)
	{
		string line=cyclometric[i];
		
		if(line.find("if")!= -1)
		{
			n++;
		}
		if(line.find("for")!= -1)
		{
			n++;
		}
		if(line.find("while")!= -1)
		{
			n++;
		}
		if(line.find("switch")!=-1)
		{
			n++;
		}
	}
	m = n+1;
	return (double) m;
}

//it will take a file and check fro n1,n2,N1,N2
int checkValuesOfThefile(string dir_path,string en1,unordered_set<string> &keywords)
{
			ifstream myfile;
			string en2=dir_path+en1;//allfies/a.cpp
			cout<<en2<<" file path\n";
 			myfile.open(en2,ios::in);

			if(myfile.is_open())
			{

				cout<<"opened\n";
            }
			else
			{
				cout<<"file did't opend\n";
				return 1;
				//	return 1;
			}
			//	ifstream operators_list;


			//========================
			int count_lines=0;//to count lines
			//========================


			//	cout<<"here"<<endl;
			//	operators_list.open("key_words.txt",ios::in);
			unordered_set<string> operators;
			unordered_set<string> operands;
			vector<string> cyclometric;
			string strline;
			//	vector<char> line;
			vector<string> eachLine;//call to each line
			//	unordered_set<char> distinct;
			//	int ko=1;
			while(!myfile.eof())
			{

				getline(myfile,strline); //get line push into the string line
				//		cout<<ko<<":"<<strline<<endl;
				//		ko++;
				/*	char ch;
				for(unsigned int i=0;i<strline.length();i++)
				{
					ch=strline[i];
					line.push_back(ch);
				}*/
				if((strline.length())>0)
				eachLine.push_back(strline);//take each line push in the vector
			}

			/*	 for(unsigned int i=0;i<line.size();i++)
	 		{
	 			if(line[i]=='\n')
				cout<<endl;

				int z=line[i];
				cout<<line[i];
				cout<<":"<<z<<endl;
	 		}
			*/
			int in = 0;
			for(unsigned int i=0;i<eachLine.size();i++)//each line in the file
			{
				string lineone;
				lineone = eachLine[i];
				if((lineone.compare("")==0) || (lineone.compare(" ")==0) || (lineone.compare("	")==0))//tab spaces
				continue;
				//	cout<<lineone<<"$->"<<endl;
				vector<string> each_word;//each word in the line
				string word;
				string line_inside=lineone;
				int pos=0;
				int first=0;
				while(1)
				{
					pos=line_inside.find(13);//remove \r
					if(pos!=-1)
						line_inside.erase(line_inside.begin() + pos);
					else
						break;
				}
				while(1)
				{
					pos=line_inside.find(9);//remove tab
					if(pos!=-1)
						line_inside.erase(line_inside.begin() + pos);
					else
						break;
				}
				//	cout<<":"<<line_inside<<":first line tab\n";
				while(1)
				{
					pos=line_inside.find(-62);
			  		if(pos!=-1)
			   			line_inside.erase(line_inside.begin() + pos);
			   	 	else
			     		break;
				}
				//		cout<<":"<<line_inside<<":first line -62\n";
				while(1)
				{
					pos=line_inside.find(-96);
			  		if(pos!=-1)
			   			line_inside.erase(line_inside.begin() + pos);
			    	else
			     		break;
				}
				//	cout<<":"<<line_inside<<":first line -96\n";
            	if(line_inside[0]==' ')//only first space remove
            	{
                	//    cout<<line_inside.length()<<"\n";
                    int i=0;
                    for(;line_inside[i];i++)//count the all spaces
                    {
                   //     cout<<line_inside[i];
                        if(line_inside[i]!=' ')
                        {
                                break;
                        }

                    }
            		//    cout<<i<<endl;
                    while(i)
                    {
                        line_inside.erase(line_inside.begin()+0);
                        i--;
                    }
            	}
          		//              cout<<":"<<line_inside<<":final line\n";
                if(line_inside=="")
                {
            		//                    cout<<"inside here\n";
                    continue;
                }



				//==================
                count_lines++;//count each proper line;
				//==================




				if((line_inside.find("main()")!=-1) || in==1)//to count cyclometriccomplexity from main
				{
					in=1;cyclometric.push_back(line_inside);
				}
					//cyclometric.push_back(line_inside);//count cyclometricComplxity from start of the program
				while(1)
				{
					pos = line_inside.find(' ');//check words in a line
					if(pos==-1)
						break;
					word=line_inside.substr(first,pos);
					if(word!="")
						each_word.push_back(word);
					line_inside=line_inside.substr(pos+1);
				}
				if(line_inside!="")
				{
					each_word.push_back(line_inside);
				}
					//	else
					//	cout<<each_word.size()<<"wordsize\n";
				for(unsigned int j=0;j<each_word.size();j++)
				{
					//	cout<<each_word[j]<<"$<-\n";
					string search=each_word[j];
					//	cout<<search<<"search\n";
					if(keywords.find(search)!= keywords.end())
					{
					//		cout<<"operators area\n";
						insertOperators(&operators,search);
					}
					else
					{
					//		cout<<"not matched area \n";
						notMatched(&keywords,&operators,&operands,search);
					}
				}
			}
			cout<<"n1 = "<<n1<<endl;
			cout<<"n2 = "<<n2<<endl;
			cout<<"N1 = "<<N1<<endl;
			cout<<"N2 = "<<N2<<endl;
			int Program_length = N1 + N2;
			int Program_vocabulary = n1+n2;
			double volume = Program_length*log2(Program_vocabulary);
			double difficulty = (double(n1)/2) * (double(N2)/double(n2));
		//	double level = (1/difficulty);
			double effort = volume*difficulty;
			double Estimated_Length = n1*log2(n1)+n2*log2(n2);
			double Time_required_to_program = effort/18;
				//double Number_of_delivered_bugs = ((pow(effort,(2/3)))/3000);
			double Number_of_delivered_bugs = volume/3000;
			double Cyclometric=cyclometricComplex(cyclometric);
			outfile<<en2<<","<<en1<<","<<n1<<","<<n2<<","<<N1<<","<<N2<<","<<Program_length<<","<<Program_vocabulary<<","<<volume<<","<<difficulty<<","<<effort<<","<<Estimated_Length<<","<<Time_required_to_program<<","<<Number_of_delivered_bugs<<","<<count_lines<<","<<Cyclometric<<","<<endl;
			cout << "Program_length : " << Program_length << endl;
			cout << "program vocabulary : " << Program_vocabulary << endl;
			cout << "Volume : " << volume << endl;
			cout << "Difficulty : " << difficulty << endl;
		//	cout << "Level : " << level << endl;
			cout << "Effort : " << effort << endl;
			cout << "Estimated_Length :"<<Estimated_Length <<endl;
			cout << "Time_required_to_program :"<<Time_required_to_program<<"(sec)"<<endl;
			cout << "Number_of_delivered_bugs :"<<Number_of_delivered_bugs<<endl;
			cout << "Number of lines in the codes:"<<count_lines<<endl;
			cout << "Cyclometric Complexcity :"<<Cyclometric<<endl;
			unordered_set<string>::iterator itr1,itr2;
			cout<<"operators\n";
			for(itr1=operators.begin();itr1!=operators.end();itr1++)
								cout << (*itr1) << endl;
			cout<<"===========================================\n";
			cout<<"operands\n";
			for(itr2=operands.begin();itr2!=operands.end();itr2++)
								cout << (*itr2) << endl;
			cout<<"===========================================\n";
			flowerL=0;
			flowerR=0;
			circleL=0;
			circleR=0;
			squareL=0;
			squareR=0;
			doubleQuo_counter=0;
			singleQuo_counter=0;
			n1=0,n2=0,N1=0,N2=0;

			myfile.close();
			return 1;
	}

//check if the the given file directory or not
//its recurssion function


void checkDir(string dir_path,string en1,unordered_set<string> &keywords)
{
	string path=dir_path+en1;
	DIR *dir;
	struct dirent *en;
	string en2;
	if(path[path.length()-1]!='/')
	{
		path+='/';

	}
	cout<<path<<":dir_path";
	
	const  char* dir_char=path.c_str();
	 cout<<dir_char<<":dir_char\n";
	dir=opendir(dir_char);
	cout<<dir<<endl;
	if(dir)
	{
		while((en=readdir(dir))!=NULL)
		{
			en2=en->d_name;
			cout<<":"<<en2<<":";
			if( (en2.find(".cpp") != -1))//only read cpp
			{
				checkValuesOfThefile(path,en2,keywords);

			}
			else
			{
				if(en2[0]=='.')
					continue;
				checkDir(path,en2,keywords);
			}
		}
		closedir(dir);
	}
	cout<<path<<"is not a directory\n";
}


//outfile and keywords file are loaded here  
int main(int argc,char* argv[])
{
	cout<<argc<<"argc\n";
	if(argc==3)
	{
	}
	else
	{
		cout<<"no arguments";
		return 1;
		}
	
	char* outfile_path=new char[100];
	cout<<"Enter the output file path with .csv extension :\n";

//	cin.clear();
//	cin.getline(outfile_path,100);
	outfile_path=argv[1];
	cout<<outfile_path<<":outfile\n";

	cout<<outfile_path<<":outfile_path\n";
	outfile.open(outfile_path,ios::trunc);
	if(outfile.is_open())
	{
		cout<<"outfile opened\n";
		outfile<<"file path"<<","<<"file_name"<<","<<"n1"<<","<<"n2"<<","<<"N1"<<","<<"N2"<<","<<"Program_length"<<","<<"Program_vocabulary"<<","<<"Volume"<<","<<"Difficulty"<<","<<"Effort"<<","<<"Estimated_Length"<<","<<"Time_required_to_program(sec)"<<","<<"Number of delivered bugs"<<","<<"Number of lines in the code"<<","<<"cyclometric complexity"<<","<<endl;
	}
	else
	{
		cout<<"outfile not found\n";
		return 1;
	}


	operators_list.open("./key_words.txt",ios::in);
	unordered_set<string> keywords;

	string key;
	if(operators_list.is_open())
	{
		cout<<"key_word file is opened\n";
		while(!operators_list.eof())
		{
			getline(operators_list,key,' ');//delimiter space
			keywords.insert(key);
	 	}
	 }

	 else
	 {
	 	cout<<"key word file did't opend"<<endl;
	 	return 1;
	 }

	DIR *dir;
	struct dirent *en;
	string en1;
	cout<<"enter the folder path:\n";

	char *dir_path=new char[100];
	cin.sync();
//	cin.clear();
	cout<<"Enter the folder path which contains cpp files\n";
	dir_path=argv[2];
	cout<<dir_path<<":dir_path\n";

//	cin.getline(dir_path,100);
	string dir_path1=dir_path;


	if(dir_path1[dir_path1.length()-1]!='/')//length
	{
		dir_path1+='/';
	}
	cout<<dir_path1<<":dir_path1";
	
	const  char* dir_char=dir_path1.c_str();
	 cout<<dir_char<<":dir_char\n";
	dir=opendir(dir_path1.c_str());
	cout<<dir<<endl;
	if(dir)//open directory check all the files if a dir prensent init is will send the dit to check dir
	{
		while((en=readdir(dir))!=NULL)
		{
			en1=en->d_name;
			cout<<":"<<en1<<":";
			if( (en1.find(".cpp") != -1))//only read cpp
			{
				checkValuesOfThefile(dir_path1,en1,keywords);
			}
			else
			{
				if(en1[0]=='.')
					continue;
				checkDir(dir_path1,en1,keywords);
			}
		}
		closedir(dir);
	}
	else
	{
		cout<<"Directory didn't found or opened\n";
	}
	operators_list.close();//keywords file is closed;
	outfile.close();//close the outfile;
	return 0;
}
