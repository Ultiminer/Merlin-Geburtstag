#ifndef EXCEPTION_HANDLING_H_
#define EXCEPTION_HANDLING_H_
#include "config.h"
#include <fstream>
#include "engine_time.h"
#include "textbox.h"
struct ENDLOG{};
struct TIMELOG {};


class Gamelog {
private:
	std::ofstream file;
public:
#ifdef EXCEPTION_CHECK
	template <class F>
	void check(F e)
	{
		if (e == nullptr) {
			print("AN EXCEPTION OCCURED DUE TO A CLASS BEING NULLPTR\n");
		}
	}
	template <class F>
	void check(F e, const char* name)
	{
		if (e == nullptr) {
			print("!!EXCEPTION!!\n");
			print("Class: "); print(name); print(" is nullptr!!\n");
		}
	}
#else
	template <class F>
	void check(F e)noexcept
	{}
	template <class F>
	void check(F e, const char* name)noexcept
	{}
#endif
	void print(const char* text)
	{
		file << text;
	}
	void print(const char text)
	{
		file << text;
	}
	void print(const float text)
	{
		file << text;
	}
	void print(const int text)
	{
		file << text;
	}
	void print(const double text)
	{
		file << text;
	}
	void print(const uint32_t text)
	{
		file << text;
	}
	Gamelog()
	{
		remove(LOGFILENAME);
		file.open(LOGFILENAME, std::ios::app);
		print(CurrDate().c_str());
	}
	~Gamelog()
	{
		print(CurrDate().c_str());
		file.close();
	}
	void reset()
	{
		file.close();
		file.open(LOGFILENAME, std::ios::app);
	}
};
	inline Gamelog& operator <<(Gamelog& lgg,const char* s)
	{
		lgg.print(s);
		return lgg;
	}
	inline Gamelog& operator <<(Gamelog& lgg, const char s)
	{
		lgg.print(s);
		return lgg;
	}
	inline Gamelog& operator <<(Gamelog& lgg, const float s)
	{
		lgg.print(s);
		return lgg;
	}
	inline Gamelog& operator <<(Gamelog& lgg, const int s)
	{
		lgg.print(s);
		return lgg;
	}
	inline  Gamelog& operator <<(Gamelog& lgg, const ENDLOG& endlog)
	{
		lgg.print("\n");
		lgg.print(">");
		return lgg;
	}
	inline  Gamelog& operator <<(Gamelog& lgg, const TIMELOG& tndl)
	{
		lgg.print(" ");
		lgg.print(SysTime());
		lgg.print(" millisecs\n");
		lgg.print(">");
		return lgg;
	}
	inline Gamelog& operator <<(Gamelog& lgg, const double d)
	{
		lgg.print(d);
		return lgg;
	}
	inline Gamelog& operator <<(Gamelog& lgg,const uint32_t val)
	{
		lgg.print(val);
		return lgg;
	}
	namespace mge{
	extern Gamelog cout;
	extern const ENDLOG endl;
	extern const TIMELOG tndl;
	extern MGE_STD_TEXTBOX* textbox;
	}

#define MGE_PRINT(x)mge::cout<<x<<mge::endl;
#define MGE_CONSOLE(x)mge::textbox->set_text(x);
#define MGE_CLEAR_CONSOLE mge::textbox->clear_text();
#define MGE_ADD_CONSOLE(x)mge::textbox->add_text(x);

#ifdef EXCEPTION_CHECK
#define MGE_CHECK(x) mge::cout.check(x,#x);
#define MGE_EXCEPT(x,condition)mge::cout<<"!!!EXCEPTION with variable "<<#x<<"occured!\n";
#else
#define MGE_EXCEPT(x)
#define MGE_CHECK(x)
#endif
#endif