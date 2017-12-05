#ifdef __cplusplus
extern "C"
{
#endif
#include "m_pd.h"

static t_class *i2c_class;  
 
typedef struct _i2c {  
	t_object  x_obj;  
} t_i2c;  
 
static void i2c_sync(t_i2c *x)
{
    post("i2c_sync");
}

static void i2c_close(t_i2c *x)
{
    post("i2c_close");
}

static void i2c_open(t_i2c *x, t_floatarg bus, t_floatarg address)
{
    post("i2c_open: bus: %d, address: %d", (int)bus, (int)address);
}

static void i2c_read(t_i2c *x, t_floatarg address)
{
    post("i2c_read: address: %d", (int)address);
}

static void i2c_write(t_i2c *x, t_floatarg address, t_floatarg value)
{
    post("i2c_write: address: %d, value: %d", (int)address, (int)value);
}

static void i2c_free(t_i2c *x)
{
    post("i2c_free");
}

static void *i2c_new(t_symbol *s, int argc, t_atom *argv)
{
	post("i2c_new");
	int bus = -1;
	int address = -1;
	if(!(argc == 0 || argc == 2))
	{
		post("i2c wants 0 or 2 arguments");
		return NULL;
	}
	if(argc == 2)
	{
		if(argv[0].a_type != A_FLOAT || argv[1].a_type != A_FLOAT)
		{
			post("i2c: bad argument(s?)");
			return NULL;
		}
		bus = argv[0].a_w.w_float;
		address = argv[1].a_w.w_float;
        i2c_open(x, bus, address);
	}
    t_i2c *x = (t_i2c *)pd_new(i2c_class);
    outlet_new(&x->x_obj, gensym("float"));
    outlet_new(&x->x_obj, gensym("float"));
    return (x);
}

void i2c_setup(void)
{
	post("i2c setup");
    i2c_class = class_new(gensym("i2c"), (t_newmethod)i2c_new,
        (t_method)i2c_free, sizeof(t_i2c), 0, 0);
    class_addmethod(i2c_class, (t_method)i2c_close,
        gensym("close"), 0);
    class_addmethod(i2c_class, (t_method)i2c_open,
        gensym("open"), A_FLOAT, A_FLOAT, 0);
    class_addmethod(i2c_class, (t_method)i2c_read,
        gensym("read"), A_FLOAT, 0);
    class_addmethod(i2c_class, (t_method)i2c_write,
        gensym("write"), A_FLOAT, A_FLOAT, 0);
    class_addmethod(i2c_class, (t_method)i2c_sync,
        gensym("sync"), 0);
    class_addcreator((t_newmethod)i2c_new, gensym("i2c"), A_GIMME, 0);
}

#ifdef __cplusplus
} /* extern "C" */
#endif


