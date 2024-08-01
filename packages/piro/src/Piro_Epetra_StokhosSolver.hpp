// @HEADER
// *****************************************************************************
//        Piro: Strategy package for embedded analysis capabilitites
//
// Copyright 2010 NTESS and the Piro contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef PIRO_EPETRA_STOKHOS_SOLVER_H
#define PIRO_EPETRA_STOKHOS_SOLVER_H

#include "EpetraExt_ModelEvaluator.h"
#include "Piro_Epetra_StokhosSolverFactory.hpp"

namespace Piro {
namespace Epetra {

  class StokhosSolver : public EpetraExt::ModelEvaluator {
  public:

    /** \name Constructors/initializers */
    //@{

    //! Constructor
    StokhosSolver(const Teuchos::RCP<Teuchos::ParameterList>& piroParams,
                  const Teuchos::RCP<const Epetra_Comm>& globalComm);

    //! Get spatial comm
    Teuchos::RCP<const Epetra_Comm> getSpatialComm() const;

    //! Get stochastic comm
    Teuchos::RCP<const Epetra_Comm> getStochasticComm() const;

    //! Get global multi-comm
    Teuchos::RCP<const EpetraExt::MultiComm> getGlobalMultiComm() const;

    //! Setup rest of model evaluator
    void setup(const Teuchos::RCP<EpetraExt::ModelEvaluator>& model,
               const Teuchos::RCP<NOX::Epetra::Observer>& noxObserver = Teuchos::null);

    //! Reset Stokhos solver parameters
    void resetSolverParameters(const Teuchos::ParameterList& new_solver_params);


    //@}

    ~StokhosSolver();


    /** \name Overridden from EpetraExt::ModelEvaluator . */
    //@{

    /** \brief . */
    Teuchos::RCP<const Epetra_Map> get_p_map(int l) const;

    /** \brief . */
    Teuchos::RCP<const Epetra_Map> get_g_map(int j) const;

    /** \brief . */
    Teuchos::RCP<const Epetra_Vector> get_p_init(int l) const;

    /** \brief . */
    //  Teuchos::RCP<Epetra_Operator> create_W() const;
    /** \brief . */
    EpetraExt::ModelEvaluator::InArgs createInArgs() const;
    /** \brief . */
    EpetraExt::ModelEvaluator::OutArgs createOutArgs() const;
    /** \brief . */
    void evalModel( const InArgs& inArgs, const OutArgs& outArgs ) const;

    //@}

    /** \name Accessors */
    //@{

    Teuchos::RCP<const Stokhos::OrthogPolyBasis<int,double> >
    getBasis() const { return sg_solver_factory.getBasis(); }

    Teuchos::RCP<const Stokhos::Quadrature<int,double> >
    getQuad() const { return sg_solver_factory.getQuad(); }

    Teuchos::RCP<Stokhos::SGModelEvaluatorBase>
    get_sg_model() const { return sg_nonlin_model; }

    //! Set initial solution polynomial
    void set_x_sg_init(const Stokhos::EpetraVectorOrthogPoly& x_sg_in) {
      sg_nonlin_model->set_x_sg_init(x_sg_in);
    }

    //! Return initial SG x
    Teuchos::RCP<const Stokhos::EpetraVectorOrthogPoly>
    get_x_sg_init() const {
      return sg_nonlin_model->get_x_sg_init();
    }

    //! Set initial parameter polynomial
    void set_p_sg_init(int i, const Stokhos::EpetraVectorOrthogPoly& p_sg_in) {
      sg_nonlin_model->set_p_sg_init(i, p_sg_in);
    }

    //! Get initial parameter polynomial
    Teuchos::RCP<const Stokhos::EpetraVectorOrthogPoly>
    get_p_sg_init(int l) const {
      return sg_nonlin_model->get_p_sg_init(l);
    }

    //! Create vector orthog poly using x map and owned sg map
    Teuchos::RCP<Stokhos::EpetraVectorOrthogPoly>
    create_x_sg(Epetra_DataAccess CV = Copy,
                const Epetra_Vector* v = NULL) const {
      return sg_nonlin_model->create_x_sg(CV, v);
    }

    //! Create vector orthog poly using p map
    Teuchos::RCP<Stokhos::EpetraVectorOrthogPoly>
    create_p_sg(int l, Epetra_DataAccess CV = Copy,
                const Epetra_Vector* v = NULL) const {
      return sg_nonlin_model->create_p_sg(l, CV, v);
    }

    //! Create vector orthog poly using g map
    Teuchos::RCP<Stokhos::EpetraVectorOrthogPoly>
    create_g_sg(int l, Epetra_DataAccess CV = Copy,
                const Epetra_Vector* v = NULL) const;

    //! Create multi-vector orthog poly using g map
    Teuchos::RCP<Stokhos::EpetraMultiVectorOrthogPoly>
    create_g_mv_sg(int l, int num_vecs, Epetra_DataAccess CV = Copy,
                   const Epetra_MultiVector* v = NULL) const;

    //@}

  private:

    /** \brief . */
    Teuchos::RCP<const Epetra_Map> get_x_map() const;
    /** \brief . */
    Teuchos::RCP<const Epetra_Map> get_f_map() const;
    /** \brief . */
    Teuchos::RCP<const Epetra_Vector> get_x_init() const;

  private:

    Teuchos::RCP<Teuchos::ParameterList> piroParams;
    Piro::Epetra::StokhosSolverFactory sg_solver_factory;
    Teuchos::RCP<Stokhos::SGModelEvaluatorBase> sg_nonlin_model;
    Teuchos::RCP<Stokhos::SGInverseModelEvaluator> sg_solver;

  };

}
}
#endif
