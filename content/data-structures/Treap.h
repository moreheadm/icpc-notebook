/**
 * Author: Nalin Bhardwaj
 * Date: 2020-01-25
 * License: CC0
 * Source: Folklore/self - https://www.codechef.com/viewsolution/11276291
 * Description: Treap with lazy propogation and climbing for reverse lookup.
 * Time: Split and merge are $O(\log N)$
 */

struct pnode {
	int sz, prior;
	int v, lz, vval = 0;
	pnode *L, *R, *P;
	pnode(pnode* l = NULL, pnode* r = NULL, int val = 0)
	{
		L = l;
		R = r;
		P = NULL;
		v = val;
		sz = 1;
		lz = 0;
		prior = rand();
	}
};

typedef pnode* node;

int get_sz(node t)
{
	return t?t->sz:0;
}

int get_v(node t)
{
	return t?t->v:0;
}

int get_lz(node t)
{
	return t?t->lz:0;
}

void upd_P(node& t)
{
	if(t)
	{
		if(t->L) t->L->P = t;
		if(t->R) t->R->P = t;
	}
}

void upd_sz(node& t)
{
	if(t) t->sz = get_sz(t->L)+get_sz(t->R)+1;
}

void upd_lz(node& t)
{
	if(t && t->lz)
	{
		t->vval += t->lz;
		t->v += get_sz(t)*t->lz;
		if(t->L) t->L->lz += t->lz;
		if(t->R) t->R->lz += t->lz;
		t->lz = 0;
	}
}

void upd_v(node& t)
{
	if(t)
	{
		upd_lz(t->L); upd_lz(t->R);
		t->v = get_v(t->L)+get_v(t->R)+t->vval;
	}
}

void split(node t, node& l, node& r, int key, int add)
{
	upd_lz(t); upd_lz(l); upd_lz(r);
	upd_P(t); upd_P(l); upd_P(r); 
	if(!t)
	{
		l = r = NULL;
		return;
	}
	int cur_key = add+get_sz(t->L);
	if(cur_key < key)
	{
		split(t->R, t->R, r, key, cur_key+1);
		l = t;
	}
	else
	{
		split(t->L, l, t->L, key, add);
		r = t;
	}
	upd_sz(t); upd_v(t);
	upd_sz(l); upd_v(l);
	upd_sz(r); upd_v(r);
	upd_P(t); upd_P(l); upd_P(r);
}

void merge(node& t, node l, node r)
{
	upd_lz(l); upd_lz(r); upd_lz(t);
	upd_P(l); upd_P(r); upd_P(t);
	if(!l || !r)
	{
		t = l?l:r;
		return;
	}
	if(l->prior > r->prior)
	{
		merge(l->R, l->R, r);
		t = l;
	}
	else
	{
		merge(r->L, l, r->L);
		t = r;
	}
	upd_sz(l); upd_v(l);
	upd_sz(r); upd_v(r);
	upd_sz(t); upd_v(t);
	upd_P(l); upd_P(r); upd_P(t);
}

int climber(node t, bool add)
{
	int res = (add?get_sz(t->L)+1:0);
	if(t->P)
	{
		if(t->P->R)
		{
			if(t->P->R->prior == t->prior) res += climber(t->P,1);
			else res += climber(t->P, 0);
		}
		else res += climber(t->P, 0);
	}

	return res;
}

void printer(node t, lli add = 0)
{
	if(t)
	{
		printer(t->L, add);
		cerr << t->v << " " << t->tr << " " << t->vval << " " << t->prior << " " << add+get_sz(t->L) << "\n";
		printer(t->R, add+get_sz(t->L)+1);
	}
}

void fix(node& t)
{
	if(t)
	{
		if(t->P) t->P = NULL;
	}
}

// Initialise
srand(time(NULL));

// Call after each qry/upd, root is overall root of running treap.
fix(root);
