/**
* @brief Structure representing various model parameters and configurations.
* 
* This structure contains parameters for different models such as Ising, XYZ, Kitaev, Heisenberg, QSM, 
* Rosenzweig-Porter, Ultrametric, Aubry-Andre, and Power Law Random Bandwidth. It also includes methods 
* for resizing vectors and setting default values.
* 
* Members:
* - modTyp: Model type.
* - modRanN: Number of random states.
* - modRanSeed: Seed for the random number generator.
* - modRanNIdx: Index of the random state.
* - eth: ETH related parameters.
* - modMidStates: States in the middle of the spectrum.
* - modEnDiff: Tolerance for the energy difference of the states in offdiagonal.
* - operators: Operators to be calculated for the model.
* 
* Ising Model Parameters:
* - J1: Spin exchange.
* - hz: Perpendicular field.
* - hx: Transverse field.
* 
* XYZ Model Parameters:
* - J2: Next nearest neighbors exchange.
* - eta1: Eta1 parameter.
* - eta2: Eta2 parameter.
* - dlt1: Delta1 parameter.
* - dlt2: Delta2 parameter.
* 
* Kitaev Model Parameters:
* - Kx_: Kx parameter.
* - Ky_: Ky parameter.
* - Kz_: Kz parameter.
* 
* Heisenberg Model Parameters:
* - heiJ_: J parameter.
* - heiDlt_: Delta parameter.
* - heiHx_: Hx parameter.
* - heiHz_: Hz parameter.
* 
* QSM Model Parameters:
* - qsm: QSM model parameters.
* 
* Rosenzweig-Porter Model Parameters:
* - rosenzweig_porter: Rosenzweig-Porter model parameters.
* 
* Ultrametric Model Parameters:
* - ultrametric: Ultrametric model parameters.
* 
* Quadratic Model Parameters:
* - q_gamma: Mixing quadratic states parameter.
* - q_manifold: Use the degenerate manifold flag.
* - q_manybody: Use the many body calculation flag.
* - q_randomCombNum: Number of random combinations for the average.
* - q_realizationNum: Number of realizations for the average.
* - q_shuffle: Shuffle the states flag.
* - q_broad: Broadening for spectral function.
* 
* Aubry-Andre Model Parameters:
* - aubry_andre: Aubry-Andre model parameters.
* 
* Power Law Random Bandwidth Model Parameters:
* - power_law_random_bandwidth: Power Law Random Bandwidth model parameters.
* 
* Methods:
* - resizeKitaev: Resizes the Kitaev model vectors.
* - resizeHeisenberg: Resizes the Heisenberg model vectors.
* - resizeQSM: Resizes the QSM model vectors.
* - resizeRP: Resizes the Rosenzweig-Porter model vectors.
* - resizeUM: Resizes the Ultrametric model vectors.
* - getRanReal(uint i): Returns the random realization at index i.
* - getRanReal(): Returns the current random realization.
* - setDefault(): Sets default values for the parameters.
* - checkComplex(): Checks whether the model itself is complex.
*/

#ifndef USER_INTERFACE_PARAMS_MOD_HPP
#define USER_INTERFACE_PARAMS_MOD_HPP

#include "./user_interface_include.hpp"

namespace UI_PARAMS
{
	// ----------------------------------------------------------------

	struct ModP 
	{
		// ################################## TYPE ##################################
		
		UI_PARAM_CREATE_DEFAULT(modTyp, MY_MODELS, MY_MODELS::ISING_M);
		UI_PARAM_CREATE_DEFAULTV(modRanN, uint);			// number of random states
		UI_PARAM_CREATE_DEFAULT(modRanSeed, u64, 0);		// seed for the random number generator
		UI_PARAM_CREATE_DEFAULT(modRanNIdx, uint, 0);		// index of the random state
		
		// eth related
		UI_PARAM_CREATE_DEFAULT(eth_entro, bool, false);
		UI_PARAM_CREATE_DEFAULT(eth_susc, bool, true);
		UI_PARAM_CREATE_DEFAULT(eth_ipr, bool, true);
		UI_PARAM_CREATE_DEFAULT(eth_offd, bool, false);
		UI_PARAM_CREATE_DEFAULTV(eth_end, double);

		UI_PARAM_CREATE_DEFAULTD(modMidStates, double, 1.0);// states in the middle of the spectrum
		UI_PARAM_CREATE_DEFAULTD(modEnDiff, double, 1.0);	// tolerance for the energy difference of the states in offdiagonal
		std::vector<std::string> operators;					// operators to be calculated for the model

		// ##########################################################################
		
		// ########################## I N T E R A C T I N G #########################
		
		// ##########################################################################

		// ############## ISING ################
		
		UI_PARAM_STEP(double, J1, 1.0);			// spin exchange
		UI_PARAM_STEP(double, hz, 1.0);			// perpendicular field
		UI_PARAM_STEP(double, hx, 1.0);			// transverse field

		// ############### XYZ #################		
		
		UI_PARAM_STEP(double, J2, 2.0);			// next nearest neighbors exchange
		UI_PARAM_STEP(double, eta1, 0.5);
		UI_PARAM_STEP(double, eta2, 0.5);
		UI_PARAM_STEP(double, dlt1, 0.3);
		UI_PARAM_STEP(double, dlt2, 0.3);

		// ############# KITAEV ################

		v_1d<double> Kx_;
		v_1d<double> Ky_;
		v_1d<double> Kz_;
		void resizeKitaev(const size_t Ns)
		{
			this->Kx_.resize(Ns);
			this->Ky_.resize(Ns);
			this->Kz_.resize(Ns);
		};

		// ########### HEISENBERG ##############

		v_1d<double> heiJ_;
		v_1d<double> heiDlt_;
		v_1d<double> heiHx_;
		v_1d<double> heiHz_;

		void resizeHeisenberg(const size_t Ns)
		{
			this->heiJ_.resize(Ns);
			this->heiDlt_.resize(Ns);
			this->heiHx_.resize(Ns);
			this->heiHz_.resize(Ns);
		};

		// ############### QSM #################

		struct qsm_t
		{
			UI_PARAM_CREATE_DEFAULTD(qsm_N, size_t, 1);
			UI_PARAM_CREATE_DEFAULTD(qsm_Ntot, size_t, 1);
			UI_PARAM_CREATE_DEFAULTD(qsm_gamma, double, 1.0);
			UI_PARAM_CREATE_DEFAULTD(qsm_g0, double, 1.0);

			UI_PARAM_CREATE_DEFAULTV(qsm_alpha, double);
			UI_PARAM_CREATE_DEFAULTV(qsm_xi, double);
			UI_PARAM_CREATE_DEFAULTV(qsm_h, double);
			void resizeQSM()
			{
				auto _N = this->qsm_Ntot_ - this->qsm_N_;
				if (_N < 0)
					return;
				this->qsm_alpha_r_ = 0;
				this->qsm_alpha_.resize(this->qsm_Ntot_ - this->qsm_N_);
				this->qsm_xi_r_ = 0;
				this->qsm_xi_.resize(this->qsm_Ntot_ - this->qsm_N_);
				this->qsm_h_r_ = 0;
				this->qsm_h_.resize(_N);
			};
		} qsm;

		// ######### ROSENZWEIG PORTER #########

		struct rosenzweig_porter_t
		{
			UI_PARAM_CREATE_DEFAULTV(rp_g, double);
			UI_PARAM_CREATE_DEFAULTD(rp_single_particle, bool, 0);
			UI_PARAM_CREATE_DEFAULTD(rp_be_real, bool, 1);
			UI_PARAM_CREATE_DEFAULTD(rp_g_sweep_n, int, 1);

			void resizeRP()
			{
				this->rp_g_.resize(this->rp_g_sweep_n_);
			};

		} rosenzweig_porter;

		// ############ ULTRAMETRIC ############

		struct ultrametric_t
		{
			UI_PARAM_CREATE_DEFAULTD(um_N, size_t, 1);
			UI_PARAM_CREATE_DEFAULTD(um_Ntot, size_t, 1);
			UI_PARAM_CREATE_DEFAULTV(um_alpha, double);
			UI_PARAM_CREATE_DEFAULTD(um_g, double, 1.0);

			void resizeUM()
			{
				auto _N = this->um_Ntot_ - this->um_N_;
				if (_N < 0)
					return;
				this->um_alpha_r_ = 0;
				this->um_alpha_.resize(_N);
			};
		} ultrametric;

		// #####################################
		// ######### Q U A D R A T I C #########
		// #####################################
		
		// for simulation
		UI_PARAM_CREATE_DEFAULT(q_gamma, uint, 1);					// mixing quadratic states
		UI_PARAM_CREATE_DEFAULT(q_manifold, bool, false);			// use the degenerate manifold?
		UI_PARAM_CREATE_DEFAULT(q_manybody, bool, true);			// use the many body calculation?
		UI_PARAM_CREATE_DEFAULT(q_randomCombNum, uint, 100);		// number of random combinations for the average (to choose from)
		UI_PARAM_CREATE_DEFAULT(q_realizationNum, uint, 100);		// number of realizations for the average
		UI_PARAM_CREATE_DEFAULT(q_shuffle, bool, true);				// shuffle the states?
		UI_PARAM_CREATE_DEFAULTD(q_broad, double, 0.1);				// broadening for spectral function

		// ########### AUBRY_ANDRE ############
		
		struct aubry_andre_t
		{
			UI_PARAM_STEP(double, aa_J, 1.0);						// hopping
			UI_PARAM_STEP(double, aa_lambda, 0.5);					// modulation strength
			UI_PARAM_STEP(double, aa_beta, (1 + std::sqrt(5)) / 2);	// phase multiplication
			UI_PARAM_STEP(double, aa_phi, 1.0);						// phase addition
		} aubry_andre;

		// ############ POWER LAW ##############

		struct power_law_random_bandwidth_t
		{
			UI_PARAM_CREATE_DEFAULTV(plrb_a, double);
			// UI_PARAM_CREATE_DEFAULTD(plrb_a, double, 1.0);
			UI_PARAM_CREATE_DEFAULTD(plrb_b, double, 1.0);
			UI_PARAM_CREATE_DEFAULTD(plrb_mb, bool, false);

		} power_law_random_bandwidth;

		// -------------------------------------

		// #####################################

		// -------------------------------------
		uint getRanReal(uint i) const { return i < this->modRanN_.size() ? this->modRanN_[i] : this->modRanN_[this->modRanN_.size()-1]; 	};
		uint getRanReal() 		const { return this->modRanNIdx_ < this->modRanN_.size() ? this->modRanN_[this->modRanNIdx_] : this->modRanN_[this->modRanN_.size()-1]; };

		void setDefault() 
		{
			UI_PARAM_SET_DEFAULT(modTyp);

			// -------------------------------------
			// default operators
			this->operators = {"sz/L", "sz/1"};
			this->modRanN_ = { 1 };

			// -------------------------------------
			// SPIN
			{
				// ising
				{
					UI_PARAM_SET_DEFAULT_STEP(J1);
					UI_PARAM_SET_DEFAULT_STEP(hz);
					UI_PARAM_SET_DEFAULT_STEP(hx);
				}
				// xyz
				{
					UI_PARAM_SET_DEFAULT_STEP(J2);
					UI_PARAM_SET_DEFAULT_STEP(eta1);
					UI_PARAM_SET_DEFAULT_STEP(eta2);
					UI_PARAM_SET_DEFAULT_STEP(dlt1);
					UI_PARAM_SET_DEFAULT_STEP(dlt2);
				}
				// kitaev
				{
					this->Kx_		= v_1d<double>(1, 1.0);
					this->Ky_		= v_1d<double>(1, 1.0);
					this->Kz_		= v_1d<double>(1, 1.0);
					this->heiJ_		= v_1d<double>(1, 1.0);
					this->heiDlt_	= v_1d<double>(1, 1.0);
					this->heiHz_	= v_1d<double>(1, 1.0);
					this->heiHx_	= v_1d<double>(1, 1.0);
				}
				// QSM
				{
					UI_PARAM_SET_DEFAULT_STRUCT(qsm, qsm_gamma);
					UI_PARAM_SET_DEFAULT_STRUCT(qsm, qsm_g0);
					UI_PARAM_SET_DEFAULT_STRUCT(qsm, qsm_Ntot);
					UI_PARAM_SET_DEFAULT_STRUCT(qsm, qsm_N);
					this->qsm.qsm_alpha_	= v_1d<double>(1, 1.0);
					this->qsm.qsm_xi_		= v_1d<double>(1, 1.0);
					this->qsm.qsm_h_		= v_1d<double>(1, 1.0);
				}
				// Rosenzweig-Porter
				{
					this->rosenzweig_porter.rp_g_ = v_1d<double>(1, 1.0);
				}
			}

			// -------------------------------------
			
			// QUADRATIC
			{
				// aubry-andre
				{
					UI_PARAM_SET_DEFAULT_STRUCT(aubry_andre, aa_J);
					UI_PARAM_SET_DEFAULT_STRUCT(aubry_andre, aa_lambda);
					UI_PARAM_SET_DEFAULT_STRUCT(aubry_andre, aa_beta);
					UI_PARAM_SET_DEFAULT_STRUCT(aubry_andre, aa_phi);
				}
			}
		}

		// -------------------------------------

		/*
		* @brief Check whether the model itself is complex...
		*/
		bool checkComplex() const
		{
			if (this->modTyp_ == MY_MODELS::FREE_FERMIONS_M)
				return true;
			return false;
		}
	};
};

#endif