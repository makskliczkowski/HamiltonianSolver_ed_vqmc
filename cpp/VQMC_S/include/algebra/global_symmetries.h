#pragma once
#ifndef GLOBALSYM_H
#define GLOBALSYM_H

#ifndef LATTICE_H
#include "../../source/src/lattices.h"
#endif // !LATTICE_H

namespace GlobalSyms {
	enum GlobalSymGenerators { U1, OTHER };

	BEGIN_ENUM(GlobalSymGenerators)
	{
		DECL_ENUM_ELEMENT(U1),
	}
	END_ENUM(GlobalSymGenerators);

	class GlobalSym {
		typedef std::function<bool(u64, double)> repType;						// type returned for checking 
	protected:
		GlobalSymGenerators name_						=						OTHER;
		repType check_;															// function that check global sym
	public:
		double val_;															// value connected to global symmetry
		std::shared_ptr<Lattice> lat_;											// lattice type to be used later on

		// constructors
		GlobalSym(std::shared_ptr<Lattice> _lat, GlobalSymGenerators _name = GlobalSymGenerators::OTHER)
			: val_(0), lat_(_lat), name_(_name)									{};

		// ---------- SETTERS -----------
		auto setFun(const repType& _fun)				-> void					{ this->check_ = _fun; };
		auto setFun(repType&& _fun)						-> void					{ this->check_ = std::move(_fun); };
		auto setName(GlobalSymGenerators _name)			-> void					{ this->name_ = _name; };

		// ---------- GETTERS -----------
		auto getName()									-> GlobalSymGenerators	{ return this->name_; };
		auto getVal()									-> double				{ return this->val_; };
		// ---------- CHECKER OVERLOAD ------------

		virtual auto operator()(u64 state) const		-> bool					{ return this->check_(state, val_); };
		virtual auto operator()(u64 state)				-> bool					{ return this->check_(state, val_); };

		// ---------- check the symmetry existence ----------
		auto check(u64 state, bool outCond) const		-> bool					{ return this->check_(state, val_) && outCond; };
	};

	/*
	* @brief describes the global check of U(1) symmetry
	*/
	inline auto U1Sym(u64 _state, double _val)			-> bool					{ return std::popcount(_state) == _val; };
};

#endif