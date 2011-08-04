/*ckwg +5
 * Copyright 2011 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include <vistk/pipeline/config.h>
#include <vistk/pipeline/datum.h>
#include <vistk/pipeline/edge.h>
#include <vistk/pipeline/edge_exception.h>
#include <vistk/pipeline/modules.h>
#include <vistk/pipeline/process.h>
#include <vistk/pipeline/stamp.h>

#include <exception>
#include <iostream>
#include <string>

static void run_test(std::string const& test_name);

int
main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Expected one argument" << std::endl;

    return 1;
  }

  std::string const test_name = argv[1];

  try
  {
    run_test(test_name);
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: Unexpected exception: " << e.what() << std::endl;

    return 1;
  }

  return 0;
}

static void test_makes_dependency();
static void test_new_has_no_data();
static void test_new_is_not_full();
static void test_new_has_count_zero();
static void test_push_datum();
static void test_peek_datum();
static void test_pop_datum();
static void test_get_datum();
static void test_required_by_downstream();
static void test_null_upstream_process();
static void test_null_downstream_process();
static void test_set_upstream_process();
static void test_set_downstream_process();

void
run_test(std::string const& test_name)
{
  if (test_name == "makes_dependency")
  {
    test_makes_dependency();
  }
  else if (test_name == "new_has_no_data")
  {
    test_new_has_no_data();
  }
  else if (test_name == "new_is_not_full")
  {
    test_new_is_not_full();
  }
  else if (test_name == "new_has_count_zero")
  {
    test_new_has_count_zero();
  }
  else if (test_name == "push_datum")
  {
    test_push_datum();
  }
  else if (test_name == "peek_datum")
  {
    test_peek_datum();
  }
  else if (test_name == "pop_datum")
  {
    test_pop_datum();
  }
  else if (test_name == "get_datum")
  {
    test_get_datum();
  }
  else if (test_name == "required_by_downstream")
  {
    test_required_by_downstream();
  }
  else if (test_name == "null_upstream_process")
  {
    test_null_upstream_process();
  }
  else if (test_name == "null_downstream_process")
  {
    test_null_downstream_process();
  }
  else if (test_name == "set_upstream_process")
  {
    test_set_upstream_process();
  }
  else if (test_name == "set_downstream_process")
  {
    test_set_downstream_process();
  }
  else
  {
    std::cerr << "Error: Unknown test: " << test_name << std::endl;
  }
}

void
test_makes_dependency()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  edge->makes_dependency();
}

void
test_new_has_no_data()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  if (edge->has_data())
  {
    std::cerr << "Error: A new edge has data in it" << std::endl;
  }
}

void
test_new_is_not_full()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  if (edge->full_of_data())
  {
    std::cerr << "Error: A new edge is full of data" << std::endl;
  }
}

void
test_new_has_count_zero()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  if (edge->datum_count())
  {
    std::cerr << "Error: A new edge has a count" << std::endl;
  }
}

void
test_push_datum()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  vistk::datum_t const dat = vistk::datum::complete_datum();
  vistk::stamp_t const stamp = vistk::stamp::new_stamp();

  vistk::edge_datum_t const edat = vistk::edge_datum_t(dat, stamp);

  edge->push_datum(edat);

  if (edge->datum_count() != 1)
  {
    std::cerr << "Error: An edge with a pushed datum does not have a count of one" << std::endl;
  }

  edge->push_datum(edat);

  if (edge->datum_count() != 2)
  {
    std::cerr << "Error: An edge with two pushed data does not have a count of two" << std::endl;
  }
}

void
test_peek_datum()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  vistk::datum_t const dat = vistk::datum::complete_datum();
  vistk::stamp_t const stamp = vistk::stamp::new_stamp();

  vistk::edge_datum_t const edat = vistk::edge_datum_t(dat, stamp);

  edge->push_datum(edat);

  vistk::edge_datum_t const get_edat = edge->peek_datum();

  if (edge->datum_count() != 1)
  {
    std::cerr << "Error: An edge removed a datum on an peek" << std::endl;
  }

  if (*get_edat.get<1>() != *stamp)
  {
    std::cerr << "Error: The edge modified a stamp on a peek" << std::endl;
  }
}

void
test_pop_datum()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  vistk::datum_t const dat = vistk::datum::complete_datum();
  vistk::stamp_t const stamp = vistk::stamp::new_stamp();

  vistk::edge_datum_t const edat = vistk::edge_datum_t(dat, stamp);

  edge->push_datum(edat);

  edge->pop_datum();

  if (edge->datum_count())
  {
    std::cerr << "Error: An edge did not remove a datum on a pop" << std::endl;
  }
}

void
test_get_datum()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  vistk::datum_t const dat = vistk::datum::complete_datum();
  vistk::stamp_t const stamp = vistk::stamp::new_stamp();

  vistk::edge_datum_t const edat = vistk::edge_datum_t(dat, stamp);

  edge->push_datum(edat);

  vistk::edge_datum_t const get_edat = edge->get_datum();

  if (edge->datum_count() != 0)
  {
    std::cerr << "Error: An edge did not remove a datum on a get" << std::endl;
  }

  if (*get_edat.get<1>() != *stamp)
  {
    std::cerr << "Error: The edge modified a stamp on a get" << std::endl;
  }
}

void
test_required_by_downstream()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  if (!edge->required_by_downstream())
  {
    std::cerr << "Error: A new edge is not marked as required by downstream" << std::endl;
  }

  edge->set_required_by_downstream(false);

  if (edge->required_by_downstream())
  {
    std::cerr << "Error: Setting the requirement by downstream failed" << std::endl;
  }

  edge->set_required_by_downstream(true);

  if (!edge->required_by_downstream())
  {
    std::cerr << "Error: Setting the requirement by downstream failed" << std::endl;
  }
}

void
test_null_upstream_process()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  vistk::process_t const process;

  bool got_exception = false;

  try
  {
    edge->set_upstream_process(process);
  }
  catch (vistk::null_process_connection_exception& e)
  {
    got_exception = true;

    (void)e.what();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: Unexpected exception: "
              << e.what() << std::endl;

    got_exception = true;
  }

  if (!got_exception)
  {
    std::cerr << "Error: Did not get expected exception "
              << "when setting a NULL process as upstream" << std::endl;
  }
}

void
test_null_downstream_process()
{
  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  vistk::process_t const process;

  bool got_exception = false;

  try
  {
    edge->set_downstream_process(process);
  }
  catch (vistk::null_process_connection_exception& e)
  {
    got_exception = true;

    (void)e.what();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: Unexpected exception: "
              << e.what() << std::endl;

    got_exception = true;
  }

  if (!got_exception)
  {
    std::cerr << "Error: Did not get expected exception "
              << "when setting a NULL process as upstream" << std::endl;
  }
}

void
test_set_upstream_process()
{
  vistk::load_known_modules();

  vistk::process_registry_t const reg = vistk::process_registry::self();
  vistk::process_registry::type_t const proc_type = vistk::process_registry::type_t("numbers");

  vistk::config_t const proc_config = vistk::config::empty_config();

  vistk::process_t const process = reg->create_process(proc_type, proc_config);

  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  edge->set_upstream_process(process);

  bool got_exception = false;

  try
  {
    edge->set_upstream_process(process);
  }
  catch (vistk::input_already_connected_exception& e)
  {
    got_exception = true;

    (void)e.what();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: Unexpected exception: "
              << e.what() << std::endl;

    got_exception = true;
  }

  if (!got_exception)
  {
    std::cerr << "Error: Did not get expected exception "
              << "when setting a second process as upstream on an edge" << std::endl;
  }
}

void
test_set_downstream_process()
{
  vistk::load_known_modules();

  vistk::process_registry_t const reg = vistk::process_registry::self();
  vistk::process_registry::type_t const proc_type = vistk::process_registry::type_t("numbers");

  vistk::config_t const proc_config = vistk::config::empty_config();

  vistk::process_t const process = reg->create_process(proc_type, proc_config);

  vistk::config_t const config = vistk::config::empty_config();

  vistk::edge_t edge = vistk::edge_t(new vistk::edge(config));

  edge->set_downstream_process(process);

  bool got_exception = false;

  try
  {
    edge->set_downstream_process(process);
  }
  catch (vistk::output_already_connected_exception& e)
  {
    got_exception = true;

    (void)e.what();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: Unexpected exception: "
              << e.what() << std::endl;

    got_exception = true;
  }

  if (!got_exception)
  {
    std::cerr << "Error: Did not get expected exception "
              << "when setting a second process as downstream on an edge" << std::endl;
  }
}