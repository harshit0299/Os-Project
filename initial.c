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