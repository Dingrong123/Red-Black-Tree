#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
#include<iostream>

namespace sjtu {

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	typedef pair<const Key, T> value_type;
	enum RBTcolour{Red,Black};

	struct RBTNode
	{
		value_type data;
		RBTNode *left;
		RBTNode *right;
		RBTNode *parent;
		RBTcolour color;

		RBTNode(value_type val,RBTcolour c=Red, RBTNode *l = NULL, RBTNode *r = NULL, RBTNode *p = NULL) :data(val), color(c),left(l), right(r), parent(p) {};

	};
/////////////////////////HERE!!!!!/////////////////////////////////////////////////
	RBTNode *root;
	size_t len;
	size_t testlen;
///////////////////////////////////////////////////////////////////////////////////
	class const_iterator;
	class iterator {
    friend class map;
	private:
		RBTNode *idxNode;
		map *myMap;
	public:
		iterator(const iterator &other)
		{
			idxNode=other.idxNode;
			myMap=other.myMap;
		}
		iterator(RBTNode *p=NULL, map *m=NULL)
		{
		    idxNode=p;
		    myMap=m;
		}

		RBTNode* prevNode(RBTNode *x)
		{
		    RBTNode *tmp,*y;
		    if(x->left!=NULL)
            {
                tmp=x->left;
                while(tmp->right!=NULL)
                    tmp=tmp->right;

                return tmp;
            }
            y=x->parent;
            while(y!=NULL&&(x==y->left))
            {
                x=y;
                y=y->parent;
            }
            return y;
		}

        RBTNode* nextNode(RBTNode *x)
        {
            RBTNode *tmp,*y;
          if(x->right!=NULL)
          {
              tmp=x->right;
              while(tmp->left!=NULL)
                tmp=tmp->left;

              return tmp;
          }

          y=x->parent;
          while((y!=NULL)&&(x==y->right))
          {
              x=y;
              y=y->parent;
          }
          return y;
        }

		iterator operator++(int)
		{
            if(idxNode==NULL) throw sjtu::invalid_iterator();

            iterator tmp=*this;

            idxNode=nextNode(idxNode);

            return tmp;
		}

		iterator & operator++()
		{
		    if(idxNode==NULL) throw sjtu::invalid_iterator();
		    idxNode=nextNode(idxNode);
		    return *this;
		}

		iterator operator--(int)
		 {
            iterator tmp=*this;
            if(myMap!=NULL&&idxNode==NULL)
            {
                RBTNode *t=myMap->root;
                if(t==NULL) throw sjtu::invalid_iterator();
                while(t->right!=NULL) t=t->right;
                idxNode=t;
                return tmp;
            }
            idxNode=prevNode(idxNode);
            if(idxNode==NULL) throw sjtu::invalid_iterator();
		     return tmp;
		 }

		iterator & operator--()
        {
            if(myMap!=NULL&&idxNode==NULL)
            {
                RBTNode *t=myMap->root;
                if(t==NULL) throw sjtu::invalid_iterator();
                while(t->right!=NULL) t=t->right;
                idxNode=t;
                return *this;
            }
            idxNode=prevNode(idxNode);
            if(idxNode==NULL) throw sjtu::invalid_iterator();
            return *this;
        }

		value_type & operator*() const
		{return idxNode->data;}
		bool operator==(const iterator &rhs) const
		{ return (idxNode==rhs.idxNode&&myMap==rhs.myMap);}
		bool operator==(const const_iterator &rhs) const
		{return (idxNode==rhs.idxNode&&myMap==rhs.myMap);}
		bool operator!=(const iterator &rhs) const
		{return !(idxNode==rhs.idxNode&&myMap==rhs.myMap);}
		bool operator!=(const const_iterator &rhs) const
        {return !(idxNode==rhs.idxNode&&myMap==rhs.myMap);}

		value_type* operator->() const noexcept
		 {
		     if(idxNode==NULL) throw sjtu::invalid_iterator();

		     return &(idxNode->data);
		 }
	};
	class const_iterator {
		friend class map;
		private:
         RBTNode *idxNode;
		const  map *myMap;
		public:
			const_iterator(const const_iterator &other)
            {
            idxNode=other.idxNode;
			myMap=other.myMap;
			}
			const_iterator(const iterator &other)
			{
            idxNode=other.idxNode;
			myMap=other.myMap;
			}

			const_iterator(RBTNode *p=NULL, const  map *m=NULL)
		    {
		    idxNode=p;
		    myMap=m;
		    }

        RBTNode* prevNode(RBTNode *x)
		{
		    RBTNode *tmp,*y;
		    if(x->left!=NULL)
            {
                tmp=x->left;
                while(tmp->right!=NULL)
                    tmp=tmp->right;

                return tmp;
            }
            y=x->parent;
            while((y!=NULL)&&(x==y->left))
            {
                x=y;
                y=y->parent;
            }
            return y;
		}

        RBTNode* nextNode(RBTNode *x)
        {
            RBTNode *tmp,*y;
          if(x->right!=NULL)
          {
              tmp=x->right;
              while(tmp->left!=NULL)
                tmp=tmp->left;

              return tmp;
          }

          y=x->parent;
          while((y!=NULL)&&(x==y->right))
          {
              x=y;
              y=y->parent;
          }

          return y;
        }

		const_iterator operator++(int)
		{
            if(idxNode==NULL) throw sjtu::invalid_iterator();

            const_iterator tmp=*this;

            idxNode=nextNode(idxNode);

            return tmp;
		}

		const_iterator & operator++()
		{
		    if(idxNode==NULL) throw sjtu::invalid_iterator();
		    idxNode=nextNode(idxNode);

		    return *this;
		}

		const_iterator operator--(int)
		 {
		     const_iterator tmp=*this;
            if(myMap!=NULL&&idxNode==NULL)
            {
                RBTNode *t=myMap->root;
                if(t==NULL) throw sjtu::invalid_iterator();
                while(t->right!=NULL) t=t->right;
                idxNode=t;
                return tmp;
            }
            idxNode=prevNode(idxNode);
            if(idxNode==NULL) throw invalid_iterator();
		     return tmp;
		 }

		const_iterator & operator--()
        {
            if(myMap!=NULL&&idxNode==NULL)
            {
                RBTNode *t=myMap->root;
                if(t==NULL) throw sjtu::invalid_iterator();
                while(t->right!=NULL) t=t->right;
                idxNode=t;
                return *this;
            }
            idxNode=prevNode(idxNode);
            if(idxNode==NULL) throw sjtu::invalid_iterator();
            return *this;
        }

		value_type & operator*() const
		{return idxNode->data;}
		bool operator==(const iterator &rhs) const
		{ return (idxNode==rhs.idxNode&&myMap==rhs.myMap);}
		bool operator==(const const_iterator &rhs) const
		{return (idxNode==rhs.idxNode&&myMap==rhs.myMap);}
		bool operator!=(const iterator &rhs) const
		{return !(idxNode==rhs.idxNode&&myMap==rhs.myMap);}
		bool operator!=(const const_iterator &rhs) const
        {return !(idxNode==rhs.idxNode&&myMap==rhs.myMap);}

		value_type* operator->() const noexcept
		 {
		     if(idxNode==NULL) throw sjtu::invalid_iterator();
		     return &(idxNode->data);
		 }
	};

	map() { root = NULL; len = testlen=0; }

	RBTNode* buildTree(RBTNode *tmp)
	{
		if (tmp == NULL) return NULL;
		RBTNode *t = new RBTNode(tmp->data, tmp->color);
		if(tmp->left!=NULL)
		{
		  t->left=buildTree(tmp->left);t->left->parent=t;
		}

		if(tmp->right!=NULL)
		{
		   t->right=buildTree(tmp->right);t->right->parent=t;
		}


		return t;
	}
	map(const map &other)
	{
		root=buildTree(other.root);
		len=other.len;
		testlen=other.testlen;
	}

	map & operator=(const map &other)
	{
	    if(this==&other)
            return *this;

       clear();
	   root=buildTree(other.root);
	   len=other.len;
       testlen=other.testlen;
	   return *this;

	}

	~map() {clear();}

    void midShow(RBTNode *t)
    {
    if(t==NULL) return;

     midShow(t->left);
     std::cout<<t->data.first.val;
     if(t->color==Black)std::cout<<"BLACK"<<" ";
     else std::cout<<"RED"<<" ";
     midShow(t->right);
    }
void pShow(RBTNode *t)
    {
    if(t==NULL) return;

     std::cout<<t->data.first.val;
     if(t->color==Black)std::cout<<"BLACK"<<" ";
     else std::cout<<"RED"<<" ";
     pShow(t->left);
     pShow(t->right);

    }
    void show()
    {
        if(root==NULL)
        {
            std::cout<<"ICAN'T"<<std::endl;
            return;
        }
        std::cout<<"***"<<root->data.first.val<<"***    ";
        midShow(root);
        std::cout<<std::endl;
    }
     void preshow()
    {
        std::cout<<"$$$"<<root->data.first.val<<"$$$"<<std::endl;
        pShow(root);
        std::cout<<std::endl;
    }
    RBTNode* searchNode(const Key &key) const
    {
        RBTNode* t = root;
        Compare cmp;
        while(t!=NULL&&(cmp(key,t->data.first)||cmp(t->data.first,key)))
        {
            if(cmp(t->data.first,key))
                t = t->right;
            else
                t = t->left;
        }
        return t;
    }
	T & at(const Key &key)
	 {
	     RBTNode *t=searchNode(key);
	     if(t==NULL)
            throw sjtu::index_out_of_bound();

        return t->data.second;
	 }
	const T & at(const Key &key) const
	{
        RBTNode *t=searchNode(key);
        if(t==NULL)
            throw sjtu::index_out_of_bound();

        return t->data.second;
	}

	T & operator[](const Key &key)
	{
	   RBTNode *t=searchNode(key);
	   if(t!=NULL)
            return t->data.second;

       pair<iterator, bool> p = insert(pair<Key, T>(key, T()));
       return p.first.idxNode->data.second;
	}

	const T & operator[](const Key &key) const
	{
	    RBTNode *t=searchNode(key);
        if(t==NULL)
            throw sjtu::index_out_of_bound();
        return t->data.second;
	}

	iterator begin()
	{
	    if(root==NULL)
	     return iterator(root,this);
        RBTNode *t=root;
        while(t->left!=NULL)
            t=t->left;

        return iterator(t,this);

	}
	const_iterator cbegin() const
	 {
	     if(root==NULL)
	     return const_iterator(root,this);
        RBTNode *t=root;
        while(t->left!=NULL)
            t=t->left;

        return const_iterator(t,this);
	 }

	iterator end() {return iterator(NULL,this);}
	const_iterator cend() const {return const_iterator(NULL,this);}

	bool empty() const { return testlen==0;}

	size_t size() const { return testlen;}

	 void clean(RBTNode * &t)
	 {
	     if(t==NULL) return;
	     clean(t->left);
	     clean(t->right);
	     delete t;
	     t=NULL;
	 }
	void clear()
	 {
        clean(root);
        len=0;
        testlen=0;
	 }

void LL(RBTNode *gp)
    {
        RBTNode *p=gp->left;
        RBTcolour col1=gp->color,col2=p->color;
        gp->color=col2; p->color=col1;
        if(gp->parent!=NULL)
        {
            if(gp==gp->parent->left) gp->parent->left=p;
            else gp->parent->right=p;
            p->parent=gp->parent;
        }
        else
        {
           root=p;p->parent=NULL;
        }


        gp->left=p->right;
        if(p->right!=NULL)p->right->parent=gp;

        p->right=gp;gp->parent=p;

    }

    void LR(RBTNode *gp)
    {
        RBTNode *p=gp->left,*x=p->right;
        RBTcolour col1=gp->color,col2=x->color;
        gp->color=col2; x->color=col1;
        if(gp->parent!=NULL)
        {
            if(gp==gp->parent->left) gp->parent->left=x;
            else gp->parent->right=x;
            x->parent=gp->parent;
        }
        else
        {
            root=x;x->parent=NULL;
        }


        p->right=x->left;
        if(x->left!=NULL) x->left->parent=p;
        p->parent=x; x->left=p;

        gp->left=x->right;
        if(x->right!=NULL) x->right->parent=gp;
        gp->parent=x; x->right=gp;

    }

    void RR(RBTNode *gp)
    {
        RBTNode *p=gp->right;
        RBTcolour col1=gp->color,col2=p->color;
        gp->color=col2; p->color=col1;

        if(gp->parent!=NULL)
        {
            if(gp==gp->parent->left) gp->parent->left=p;
            else gp->parent->right=p;
            p->parent=gp->parent;
        }

        else
        {
             root=p;p->parent=NULL;
        }



        gp->right=p->left;
        if(p->left!=NULL) p->left->parent=gp;

        p->left=gp;gp->parent=p;

    }

    void RL( RBTNode *gp)
    {
        RBTNode *p=gp->right,*x=p->left;
        RBTcolour col1=gp->color,col2=x->color;
         gp->color=col2; x->color=col1;

        if(gp->parent!=NULL)
        {
           if(gp==gp->parent->left) gp->parent->left=x;
           else gp->parent->right=x;
           x->parent=gp->parent;
        }

        else
        {
            root=x;x->parent=NULL;
        }


        gp->right=x->left;
        if(x->left!=NULL) x->left->parent=gp;
        gp->parent=x;x->left=gp;

        p->left=x->right;
        if(x->right!=NULL)x->right->parent=p;
        p->parent=x;x->right=p;


    }

    void insertAdjust(RBTNode *gp,RBTNode *p,RBTNode *t)
    {
        if(p->color==Black)
        {
             return;
        }

        if(p==root)
        {
            p->color=Black;
            return;
        }
        if(gp->left==p)
        {
            if(p->left==t) LL(gp);else LR(gp);
        }
        else
        {
           if(p->right==t) RR(gp);
           else RL(gp);
        }
        return;
    }

	pair<iterator, bool> insert(const value_type &value)
	{

	    RBTNode *t,*p,*grandP;
	    Compare judge;
	    if(root==NULL)
        {
            root=new RBTNode(value,Black);
            ++len;
            ++testlen;
            iterator p(root,this);
            return pair<iterator,bool>(p,true);
        }

        p=grandP=t=root;

        RBTNode *tt=searchNode(value.first);
        if(tt!=NULL)
            return pair<iterator,bool>(iterator(tt,this),false);
        ++testlen;
        while(true)
        {
            if(t)
            {
                if(t->left&&t->left->color==Red&&t->right&&t->right->color==Red)
                {
                    t->left->color=t->right->color=Black;
                    t->color=Red;
                    insertAdjust(grandP,p,t);
                }

                grandP=p;
                p=t;
                t=(judge(value.first,t->data.first))?t->left:t->right;
            }

            else
            {
                t=new RBTNode(value);

                if(judge(value.first,p->data.first))
                {
                    p->left=t;
                    t->parent=p;
                }

                else
                {
                     p->right=t;
                     t->parent=p;
                }
                insertAdjust(grandP,p,t);
                root->color=Black;
                iterator pos(t,this);
                ++len;
                return pair<iterator,bool>(pos,true);
            }
        }
	}

    bool isEqual(Key r1,Key r2)
    {
        Compare judge;
        return (!judge(r1,r2)&&!judge(r2,r1));
    }

    void removeAdjust(RBTNode *&p,RBTNode *&c,RBTNode *&t,Key del)
    {
        Compare judge;
        if(c->color==Red) return;
        if(c==root)
        {
            if(c->left&&c->right&&c->right->color==c->left->color)
            {
                c->color=Red;
                c->left->color=c->right->color=Black;
                return;
            }
        }

        if((c->left&&c->left->color==Black||c->left==NULL)&&(c->right&&c->right->color==Black||c->right==NULL))
        {
          if((t->left&&t->left->color==Black||t->left==NULL)&&(t->right&&t->right->color==Black||t->right==NULL))
               {
                 p->color=Black;
                 t->color=c->color=Red;
               }
          else
          {
            if(p->left==t)
            {
                if(t->left&&t->left->color==Red)
                {
                    t->left->color=Black;
                    LL(p);
                }

                else
                {
                    LR(p);
                    p->color=Black;
                }
            }

            else
            {
                if(t->right&&t->right->color==Red)
                {
                    t->right->color=Black;
                    RR(p);
                }

                else
                {
                    RL(p);
                    p->color=Black;
                }
            }
            c->color=Red;
        }
     }


     else
     {
         if(isEqual(c->data.first,del))
         {
            if(c->left&&c->right)
             {
                 if(c->right->color==Black)
                 {
                     LL(c);
                     p=c->parent;
                 }
                 return;
             }

             if(c->left)
             {
                 LL(c);
                 p=c->parent;
             }
             else
             {
               RR(c);
               p=c->parent;
             }
         }

     else
     {
         p=c;
         c=(judge(del,p->data.first))?p->left:p->right;
         t=(c==p->left?p->right:p->left);
         if(c->color==Black)
         {
             if(t==p->right)
             {
                  RR(p);
             }

             else
             {
                 LL(p);
             }
             t=(c==p->left?p->right:p->left);
             removeAdjust(p,c,t,del);
         }
     }
     }
    }


	void erase(iterator pos)
    {
	    if(pos.idxNode==NULL||pos.myMap!=this)
            throw sjtu::invalid_iterator();
        --testlen;
        Key *del= new Key(pos.idxNode->data.first);
        RBTNode *t,*p,*c;
        Compare judge;

       if(isEqual(*del,root->data.first)&&root->left==NULL&&root->right==NULL)
       {
        delete del;
           delete root;
           root=NULL;
           --len;
           return;
       }
    p=c=t=root;
    RBTNode *tmp;
    while(true)
    {
        removeAdjust(p,c,t,*del);
        if(isEqual(c->data.first,*del)&&c->left&&c->right)
        {
            tmp=c->right;
            RBTNode *record=c;
            while(tmp->left) tmp=tmp->left;
            ////c->data=tmp->data;

                if(tmp==tmp->parent->right)
                {
                    tmp->parent->right=new RBTNode(tmp->data,tmp->color,tmp->left,tmp->right,tmp->parent);
                    if(tmp->right!=NULL) tmp->right->parent=tmp->parent->right;
                }
                else
                {
                    tmp->parent->left=new RBTNode(tmp->data,tmp->color,tmp->left,tmp->right,tmp->parent);
                    if(tmp->right!=NULL) tmp->right->parent=tmp->parent->left;
                }
                tmp->color=c->color;tmp->parent=c->parent;tmp->left=c->left;tmp->right=c->right;
                if(c->parent!=NULL)
                {
                if(c==c->parent->left)c->parent->left=tmp;
                else c->parent->right=tmp;
                }

                c->left->parent=tmp;
                c->right->parent=tmp;
                if(record==root) root=tmp;
                delete c;

            delete del;
            del=new Key(tmp->data.first);
            c=tmp;
            p=c;
            c=c->right;
            t=p->left;
            continue;
        }

        if(isEqual(c->data.first,*del))
        {

            if(p->left==c)
                p->left=NULL;
            else
              p->right=NULL;
              delete del;
            delete c;
            root->color=Black;
            --len;
            return;
        }
        p=c;
        c=(judge(*del,p->data.first))?p->left:p->right;
        t=(c==p->left?p->right:p->left);
    }
 }
	size_t count(const Key &key) const
	{
	   RBTNode *p = searchNode(key);
	    if(p==NULL) return 0;

	    return 1;
	}

	iterator find(const Key &key)
	{
	    RBTNode *p=searchNode(key);

	    return iterator(p,this);
	}
	const_iterator find(const Key &key) const
	{
	     RBTNode *p=searchNode(key);
	    return const_iterator(p,this);
	}
};

}

#endif
