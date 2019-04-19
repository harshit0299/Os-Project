#include <bits/stdc++.h>
using namespace std;
struct Process_Data
{
	int num;
	int process;
	int atime; 
	int btime; 
	int priority;
	int fintime; 
	int remtime; 
	int waittime;
	int starttime;
	int Res_time;
};
struct Process_Data current;
typedef struct Process_Data P_d ;
bool idsort(const P_d& x , const P_d& y)
{
	return x.process < y.process;
}
bool arrivalsort( const P_d& x ,const P_d& y)
{
	if(x.atime < y.atime)
		return true;
	else if(x.atime > y.atime)
		return false;
	if(x.priority < y.priority)
		return true;
	else if(x.priority > y.priority)
		return false;
	if(x.process < y.process)
		return true;
	return false;
}
bool numsort( const P_d& x ,const P_d& y)
{
	return x.num < y.num;
}
struct compare
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.priority > y.priority )
			return true;
		else if( x.priority < y.priority )
			return false;
		if( x.process > y.process )
			return true;
		return false;		
	}	
};
void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" process :"<<mv[i].process<<" _time : "<<mv[i].atime<<" btime : "<<mv[i].btime<<" priority : "<<mv[i].priority<<endl;
	}
}
int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0;
	int rq_process = 0;
	int atime;
	int btime;
	int process;
	int priority;
	int n;
	int clock;
	int total_exection_time = 0;
	cout<<"Enter the number of processes\n";
	cin>>n;
	for( i= 0; i< n; i++ )
	{
		cout<<"|Process ID|\n";
		cin>>process;
		cout<<"|Arrival Time|\n";
		cin>>atime;
		cout<<"|Burst Time|\n";
		cin>>btime;
		cout<<"|Priority|\n";
		cin>>priority;
		temp.num = i+1;
		temp.atime = atime;
		temp.btime = btime;
		temp.remtime = btime;
		temp.process = process;
		temp.priority = priority;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );
    total_exection_time = total_exection_time + input[0].atime;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_exection_time >= input[i].atime )
    	{
    		total_exection_time = total_exection_time +input[i].btime;
    	}
    	else
    	{
    		int diff = (input[i].atime - total_exection_time);
    		total_exection_time = total_exection_time + diff + btime;
    	}
    }
	int Ghant[total_exection_time]={0};
	for( i= 0; i< total_exection_time; i++ )
	{
		Ghant[i]=-1;
	}
	priority_queue < P_d ,vector<Process_Data> ,compare> pq;
	queue< P_d > rq;
	int cpu_state = 0;
	int quantum = 4 ;
	current.process = -2;
	current.priority = 999999;
	for ( clock = 0; clock< total_exection_time; clock++ )
	{
		for( int j = 0; j< n ; j++ )
		{
			if(clock == input[j].atime)
			{
				pq.push(input[j]);
			}
		}
		if(cpu_state == 0)
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4; 
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1)
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().priority < current.priority )
				{
					rq.push(current);
					current = pq.top();
					pq.pop();
					quantum = 4; 
				}
			}
			else if(rq_process == 1 && (!pq.empty()))
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}
					}
		if(current.process != -2)
		{
			current.remtime--;
			quantum--;
			Ghant[clock] = current.process;
			if(current.remtime == 0) 
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.process = -2;
				current.priority = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 ) 
			{
				rq.push(current);
				current.process = -2;
				current.priority = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;
			}
		}
	}
	sort( input.begin(), input.end(), idsort );
	for(int i=0;i<n;i++)
	{
		for(int k=total_exection_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].fintime=k+1;
				break;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_exection_time;k++)
		{
			if(Ghant[k]==i+1)
			{
				input[i].starttime=k;
				break;
			}
		}
	}
	sort( input.begin(), input.end(), numsort );
	for(int i=0;i<n;i++)
	{
		input[i].Res_time=input[i].starttime-input[i].atime;
		input[i].waittime=(input[i].fintime-input[i].atime)-input[i].btime;
	}
	for(int i=0;i<n;i++)
	{
		cout<<input[i].process<<" "<<input[i].Res_time<<" "<<input[i].fintime<<" "<<input[i].waittime<<endl;
	}	
	return 0;
}