/**
 * Author: Jingbo Shang/SGTU
 * License: CC0
 * Source: SGTU notebook
 * Description: Solves exact cover problem: Given a matrix of 0s and 1s, does it have a set of rows containing exactly one 1 in each column.
 *              To reduce 9 by 9 sudoku to exact cover: We have 81 columns for cell constraint - each cell can contain only 1 integer, we have 81 columns
 *              for each row constraint - each row can contain 9 unique integers, we have 81 columns for each column constraint - each column
 *              can contain 9 unique integers and 81 columns for box constraint - each box can contain 9 unique integers. We also have
 *              9 rows for each cell representing the number we put into that cell. So, we have 729 by 324 matrix. For cell constraint,
 *              for rows corresponding to the same cell but different values, but 1 in column r*N+c. For row constraint, put 1 in the corresponding
 *              row and value column so at N*N+r*N+v. For column, put at 2*N*N+c*N+v. For box, number the boxes and put at 3*N*N+b*N+v. Then call dlx for
 *              exact cover and see which rows we choose.
 * Time: O(2^n)
 */
class ExactCover{
  private:
    vector<int> u,d,l,r,C,R,head,tail;
    int head0,tail0,seed;
    void cover(int x){
      int i=x,j;
      r[l[x]]=r[x];
      l[r[x]]=l[x];
      while((i=d[i])!=x){
        j=i;
        while((j=l[j])!=i){
          u[d[j]]=u[j];
          d[u[j]]=d[j];
          R[C[j]]--;
        }
      }
    }
    void uncover(int x){
      int i=x,j;
      while((i=u[i])!=x){
        j=i;
        while((j=r[j])!=i){
          u[d[j]]=j;
          d[u[j]]=j;
          R[C[j]]++;
        }
      }
      r[l[x]]=x;
      l[r[x]]=x;
    }
  public:
    vector<int> ans;
    void resize(int n){
      u.resize(1,0);
      d.resize(1,0);
      l.resize(1,0);
      r.resize(1,0);
      C.resize(1,-1);
      R.resize(1,-1);
      head.resize(n,-1);
      tail.resize(n,-1);
      ans.resize(n,0);
      head0=tail0=0;
    }
    void add(vector<int> a,bool must=true){
      u.push_back(u.size()+a.size());
      if(must){
        l.push_back(tail0);
        r.push_back(head0);
        tail0=l[r[d.size()]]=r[l[d.size()]]=d.size();
      }else{
        l.push_back(l.size());
        r.push_back(r.size());
      }
      C.push_back(C.size());
      R.push_back(a.size());
      int n=u.size(),m=a.size(),i,j;
      for(i=0;i<m;i++){
        j=a[i];
        if(head[j]==-1){
          l.push_back(n+i);
          r.push_back(n+i);
          head[j]=n+i;
          tail[j]=n+i;
        }else{
          l.push_back(tail[j]);
          r.push_back(head[j]);
          tail[j]=r[l[n+i]]=l[r[n+i]]=n+i;
        }
        u.push_back(n+i-1);
        d.push_back(n+i);
        C.push_back(C.back());
        R.push_back(j);
      }
      d.push_back(n-1);
    }
    void select(int a){
      ans[a]=1;
      a=head[a];
      if(a==-1)
        return;
      int x=a;
      while((x=r[x])!=a)
        cover(C[x]);
      cover(C[a]);
    }
    bool search(){
      if(r[0]==0)
        return true;
      int x,i,j,min=0x7fffffff;
      i=0;
      while((i=r[i])!=0)
        if(R[i]<min||!(++seed&3)&&R[i]==min)
          min=R[x=i];
      cover(i=x);
      while((i=d[i])!=x){
        j=i;
        while((j=r[j])!=i)
          cover(C[j]);
        ans[R[i]]=1;
        if(search())
          return true;
        ans[R[i]]=0;
        while((j=l[j])!=i)
          uncover(C[j]);
      }
      uncover(x);
      return false;
    }
};
