#include <iostream>
#include <set>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define col 100
#define ll long long int

class AImatrix
{
	public:
		set<pair<ll,pair<ll,ll> > >score_list;
};
int result=-1;

ll factorial(ll val){
	ll pr=1;
	while(val){
		pr*=val;
		val--;
	}
	return pr;
}

map<vector<vector<ll> >,AImatrix> mpset;

void print(int matrix[100][100],int n){
	for(int i=0;i<n;i++){
		if(i>0){
			for(int p=0;p<n;p++){
				cout<<"- ";
			}
			cout<<endl;
		}
		for(int j=0;j<n;j++){
			if(j==n-1){
				if(matrix[i][j]==-1){
					cout<<" "<<endl;
				}
				else if(matrix[i][j]==0){
					cout<<"O"<<endl;
				}
				else{
					cout<<"X"<<endl;
				}
			}
			else{
				if(matrix[i][j]==-1){
					cout<<" |";
				}
				else if(matrix[i][j]==0){
					cout<<"O|";
				}
				else{
					cout<<"X|";
				}
			}
		}
	}
}
int full(int matrix[100][100],int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(matrix[i][j]==-1){
				return 1;
			}
		}
	}
	return 0;
}
int check(int matrix[100][100],int row,int column,int val,int n){
	int flag=0;
	for(int j=0;j<n;j++){
		if(matrix[row][j]!=val){
			flag=1;
			break;
		}
	}
	if(flag==0){
		return 1;
	}
	flag=0;
	for(int j=0;j<n;j++){
		if(matrix[j][column]!=val){
			flag=1;
			break;
		}
	}
	if(flag==0){
		return 1;
	}
	if(row==column){
		flag=0;
		for(int i=0;i<n;i++){
			if(matrix[i][i]!=val){
				flag=1;
				break;
			}
		}
		if(flag==0){
			return 1;
		}
	}
	if(row+column==n-1){
		flag=0;
		for(int i=0;i<n;i++){
			if(matrix[i][n-1-i]!=val){
				flag=1;
				break;
			}
		}
		if(flag==0){
			return 1;
		}

	}
	return 0;
}


pair<ll,pair<ll,ll> > decisionTree(int matrix[100][100],int n,int turn,int depth){
	int arr[100][100];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			arr[i][j] = matrix[i][j];
		}
	}
	vector<vector<ll> >v;
	for(int i=0;i<n;i++){
		vector<ll>st;
		for(int j=0;j<n;j++){
			st.push_back(arr[i][j]);
		}
		v.push_back(st);
	}
	map<vector<vector<ll> >,AImatrix>:: iterator punnu = mpset.find(v);
	if(punnu!=mpset.end()){
		if(turn==0){
			set<pair<ll,pair<ll,ll> > >::iterator it = mpset[v].score_list.end();
			it--;
			pair<ll,pair<ll,ll> > passing = (*it);
			return passing;
		}
		else{
			set<pair<ll,pair<ll,ll> > >::iterator it = mpset[v].score_list.begin();
			pair<ll,pair<ll,ll> > passing = (*it);
			return passing;
		}
	}
	//cout<<mpset.size()<<endl;
	AImatrix temp;
	if(turn==0){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(arr[i][j]==-1){
					arr[i][j]=0;
					int d = check(arr,i,j,turn,n);
					if(d==1){
						temp.score_list.insert(make_pair(10,make_pair(i,j)));
						mpset[v]=temp;
						pair<ll,pair<ll,ll> > pp = make_pair(10,make_pair(i,j));
						return pp;
					}
					else{
						if(full(arr,n)==0){
							temp.score_list.insert(make_pair(0,make_pair(i,j)));
						}
						else{
							pair<ll,pair<ll,ll> > temporary = decisionTree(arr,n,1,depth+1);
							temp.score_list.insert(make_pair(temporary.first,make_pair(i,j)));
							if(temporary.first==10){
								mpset[v]=temp;
								pair<ll,pair<ll,ll> > pp = make_pair(10,make_pair(i,j));
								return pp;
							}
						}
					}
					arr[i][j]=-1;
				}
			}
		}
		mpset[v]=temp;
		set<pair<ll,pair<ll,ll> > >::iterator it = temp.score_list.end();
		it--;
		pair<ll,pair<ll,ll> > passing = (*it);
		return passing;
	}
	else{
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(arr[i][j]==-1){
					arr[i][j]=1;
					int d = check(arr,i,j,turn,n);
					if(d==1){
						temp.score_list.insert(make_pair(-10,make_pair(i,j)));
						mpset[v]=temp;
						pair<ll,pair<ll,ll> > pp = make_pair(-10,make_pair(i,j));
						return pp;
					}
					else{
						if(full(arr,n)==0){
							temp.score_list.insert(make_pair(0,make_pair(i,j)));
						}
						else{
							pair<ll,pair<ll,ll> > temporary = decisionTree(arr,n,0,depth+1);
							temp.score_list.insert(make_pair(temporary.first,make_pair(i,j)));
							if(temporary.first==-10){
								mpset[v]=temp;
								pair<ll,pair<ll,ll> > pp = make_pair(-10,make_pair(i,j));
								return pp;
							}
						}
					}
					arr[i][j]=-1;
				}
			}
		}
		mpset[v]=temp;
		set<pair<ll,pair<ll,ll> > >::iterator it = temp.score_list.begin();
		pair<ll,pair<ll,ll> > tt = (*it);
		return tt;
	}

}


void turnAI(int matrix[100][100],int n){
	int newmatrix[100][100];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			newmatrix[i][j]=matrix[i][j];
		}
	}
	pair<ll,pair<ll,ll> > finalans = decisionTree(newmatrix,n,0,1);
	//cout<<finalans.score<<" "<<finalans.x<<" "<<finalans.y<<" "<<county<<endl;
	matrix[finalans.second.first][finalans.second.second]=0;
	print(matrix,n);
	int d = check(matrix,finalans.second.first,finalans.second.second,0,n);
	if(d==1){
		cout<<"Computer Wins"<<endl;
		result=1;
		return;
	}
}

void turnuser(int matrix[100][100],int n){
	cout<<"Enter Your Choice\n";
	int x,y;
	cin>>x>>y;
	while(matrix[x][y]!=-1){
		cout<<"Enter Your Choice\n";
		cin>>x>>y;
	}
	matrix[x][y]=1;
	print(matrix,n);
	int d = check(matrix,x,y,1,n);
	if(d==1){
		cout<<"User Wins"<<endl;
		result=1;
		return;
	}
	int p = full(matrix,n);
	if(p==0){
		cout<<"Game Drawn\n";
		result=1;
		return;
	}
	turnAI(matrix,n);
}

int main(){
	cout<<"Enter size of matrix"<<endl;
	int n;
	cin>>n;
	int matrix[100][100];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j]=-1;
		}
	}
	print(matrix,n);
	while(full(matrix,n) && result==-1)
		turnuser(matrix,n);
	return 0;
}