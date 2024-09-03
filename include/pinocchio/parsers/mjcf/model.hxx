//
// Copyright (c) 2016-2023 CNRS INRIA
//

#ifndef __pinocchio_parsers_mjcf_model_hxx__
#define __pinocchio_parsers_mjcf_model_hxx__

#include "pinocchio/parsers/mjcf.hpp"
#include "pinocchio/parsers/mjcf/mjcf-graph.hpp"
#include "pinocchio/multibody/model.hpp"
#include "pinocchio/algorithm/contact-info.hpp"

namespace pinocchio
{
  namespace mjcf
  {
    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModel(
      const std::string & filename,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      const bool verbose)
    {
      return buildModelFromXML(filename, model, verbose);
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModelFromXML(
      const std::string & xmlStr,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      const bool verbose)
    {
      ::pinocchio::urdf::details::UrdfVisitor<Scalar, Options, JointCollectionTpl> visitor(model);

      typedef ::pinocchio::mjcf::details::MjcfGraph MjcfGraph;

      MjcfGraph graph(visitor, xmlStr);
      if (verbose)
        visitor.log = &std::cout;

      graph.parseGraphFromXML(xmlStr);

      // Use the Mjcf graph to create the model
      graph.parseRootTree();

      return model;
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModel(
      const std::string & filename,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      PINOCCHIO_STD_VECTOR_WITH_EIGEN_ALLOCATOR(RigidConstraintModel) & contact_models,
      const bool verbose)
    {
      return buildModelFromXML(filename, model, contact_models, verbose);
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModelFromXML(
      const std::string & xmlStr,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      PINOCCHIO_STD_VECTOR_WITH_EIGEN_ALLOCATOR(RigidConstraintModel) & contact_models,
      const bool verbose)
    {
      ::pinocchio::urdf::details::UrdfVisitor<Scalar, Options, JointCollectionTpl> visitor(model);

      typedef ::pinocchio::mjcf::details::MjcfGraph MjcfGraph;

      MjcfGraph graph(visitor, xmlStr);
      if (verbose)
        visitor.log = &std::cout;

      graph.parseGraphFromXML(xmlStr);

      // Use the Mjcf graph to create the model
      graph.parseRootTree();
      graph.parseContactInformation(model, contact_models);

      return model;
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModel(
      const std::string & filename,
      const typename ModelTpl<Scalar, Options, JointCollectionTpl>::JointModel & rootJoint,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      const bool verbose,
      const std::string rootJointName)
    {
      return buildModelFromXML(filename, rootJoint, model, verbose, rootJointName);
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModelFromXML(
      const std::string & xmlStr,
      const typename ModelTpl<Scalar, Options, JointCollectionTpl>::JointModel & rootJoint,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      const bool verbose,
      const std::string rootJointName)
    {
      ::pinocchio::urdf::details::UrdfVisitorWithRootJoint<Scalar, Options, JointCollectionTpl>
        visitor(model, rootJoint, rootJointName);

      typedef ::pinocchio::mjcf::details::MjcfGraph MjcfGraph;

      MjcfGraph graph(visitor, xmlStr);
      if (verbose)
        visitor.log = &std::cout;

      graph.parseGraphFromXML(xmlStr);

      // Use the Mjcf graph to create the model
      graph.parseRootTree();

      return model;
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModel(
      const std::string & filename,
      const typename ModelTpl<Scalar, Options, JointCollectionTpl>::JointModel & rootJoint,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      PINOCCHIO_STD_VECTOR_WITH_EIGEN_ALLOCATOR(RigidConstraintModel) & contact_models,
      const bool verbose)
    {
      return buildModelFromXML(filename, rootJoint, model, contact_models, verbose);
    }

    template<typename Scalar, int Options, template<typename, int> class JointCollectionTpl>
    ModelTpl<Scalar, Options, JointCollectionTpl> & buildModelFromXML(
      const std::string & xmlStr,
      const typename ModelTpl<Scalar, Options, JointCollectionTpl>::JointModel & rootJoint,
      ModelTpl<Scalar, Options, JointCollectionTpl> & model,
      PINOCCHIO_STD_VECTOR_WITH_EIGEN_ALLOCATOR(RigidConstraintModel) & contact_models,
      const bool verbose)
    {
      ::pinocchio::urdf::details::UrdfVisitorWithRootJoint<Scalar, Options, JointCollectionTpl>
        visitor(model, rootJoint);

      typedef ::pinocchio::mjcf::details::MjcfGraph MjcfGraph;

      MjcfGraph graph(visitor, xmlStr);
      if (verbose)
        visitor.log = &std::cout;

      graph.parseGraphFromXML(xmlStr);

      // Use the Mjcf graph to create the model
      graph.parseRootTree();
      graph.parseContactInformation(model, contact_models);

      return model;
    }

  } // namespace mjcf
} // namespace pinocchio

#endif // __pinocchio_parsers_mjcf_model_hxx__
