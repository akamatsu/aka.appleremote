// aka.appleremote.c
// Copyright ý 2007 by Masayuki Akamatsu

#include "ext.h"
#include "AppleRemoteWrapper.h"


typedef struct akaappleremote
{
	t_object	obj;
	void		*out;
	Boolean		opened;
	Boolean		exclusive;
} t_akaappleremote;

void akaappleremote_bang(t_akaappleremote *x);
void akaappleremote_int(t_akaappleremote *x, long n);
void akaappleremote_open(t_akaappleremote *x);
void akaappleremote_close(t_akaappleremote *x);
void akaappleremote_exclusive(t_akaappleremote *x, long n);
void akaappleremote_output(t_akaappleremote *x, t_symbol *s, short ac, t_atom *av); 
void akaappleremtoe_callback(t_akaappleremote *x, short id, Boolean pressed);
void akaappleremote_assist(t_akaappleremote *x, void *b, long m, long a, char *s);
void akaappleremote_free(t_akaappleremote *x);
void *akaappleremote_new(t_symbol *s, short argc, t_atom *argv);

void	*akaappleremote_class;


//----------------------------------------------------------------

void main()
{
	setup((t_messlist **)&akaappleremote_class, 
		  (method)akaappleremote_new, 
		  (method)akaappleremote_free, 
		  (short)sizeof(t_akaappleremote), 
		  0L, 
		  A_GIMME, 0);
	
	addbang((method)akaappleremote_bang);
	addint((method)akaappleremote_int);
	addmess((method)akaappleremote_open, "open", 0);
	addmess((method)akaappleremote_close, "close", 0);
	addmess((method)akaappleremote_exclusive, "exclusive", A_DEFLONG, 0);
	addmess((method)akaappleremote_assist,"assist",A_CANT,0);
	
	post("aka.appleremote 1.0-UB by Masayuki Akamatsu");
}

//-----------------------------------------------------------------------------------------------------

void akaappleremote_bang(t_akaappleremote *x)
{
}

void akaappleremote_int(t_akaappleremote *x, long n)
{
	if (n == 0)
		akaappleremote_close(x);
	else
		akaappleremote_open(x);
}

void akaappleremote_open(t_akaappleremote *x)
{
	
	if (initAppleRemote())
	{
		setExclusiveMode(x->exclusive);
		setCallBack((void *)akaappleremtoe_callback, (void *)x);
		startListening();
		x->opened = true;
	}
	else
	{
		error("aka.appleremote: Can't open Apple Remote device.");
	}
}

void akaappleremote_close(t_akaappleremote *x)
{
	if (x->opened)
	{
		terminateAppleRemote();
		x->opened = false;
	}
}

void akaappleremote_exclusive(t_akaappleremote *x, long n)
{
	if ( n==0 )
		x->exclusive = false;
	else
		x->exclusive = true;
}

//-----------------------------------------------------------------------------------------------------

void akaappleremote_output(t_akaappleremote *x, t_symbol *s, short ac, t_atom *av)
{
	t_atom list[2];
	
	SETLONG(list, -1);
	SETLONG(list + 1, -1);
	if (ac==2)
	{
		if (av[0].a_type == A_LONG)
			SETLONG(list, av[0].a_w.w_long);
		if (av[1].a_type == A_LONG)
			SETLONG(list + 1, av[1].a_w.w_long);
	}
	outlet_list(x->out, 0L, 2, list);
}

void akaappleremtoe_callback(t_akaappleremote *x, short id, Boolean pressed)
{
	t_atom	av[2];
	
	SETLONG(av, id);
	SETLONG(av + 1, pressed);
	defer(x, akaappleremote_output, gensym("output"), 2, av); 
}

//-----------------------------------------------------------------------------------------------------

void akaappleremote_assist(t_akaappleremote *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET)
	{
		switch (a)
		{
			case 0: sprintf(s,"bang"); break;
		}
	}
	else	// ASSIST_OUTLET
	{
		switch(a)
		{
			case 0: sprintf(s,"int"); break;
			case 1: sprintf(s,"int"); break;
		}
	}
}

//-----------------------------------------------------------------------------------------------------

void akaappleremote_free(t_akaappleremote *x)
{
	akaappleremote_close(x);
}

void *akaappleremote_new(t_symbol *s, short argc, t_atom *argv)
{
	t_akaappleremote *x = (t_akaappleremote *)newobject(akaappleremote_class);
	x->out = listout(x);
	x->opened = false;
	x->exclusive = true;
	
	return x;
}


//-----------------------------------------------------------------------------------------------------


