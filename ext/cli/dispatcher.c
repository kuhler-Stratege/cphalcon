
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  |          Rack Lin <racklin@gmail.com>                                  |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/object.h"
#include "kernel/exception.h"

/**
 * Phalcon\CLI\Dispatcher
 *
 * Dispatching is the process of taking the command-line arguments, extracting the module name,
 * task name, action name, and optional parameters contained in it, and then
 * instantiating a task and calling an action on it.
 *
 *<code>
 *
 *	$di = new Phalcon\DI();
 *
 *	$dispatcher = new Phalcon\CLI\Dispatcher();
 *
 *  $dispatcher->setDI($di);
 *
 *	$dispatcher->setTaskName('posts');
 *	$dispatcher->setActionName('index');
 *	$dispatcher->setParams(array());
 *
 *	$handle = $dispatcher->dispatch();
 *
 *</code>
 */


/**
 * Sets the default task suffix
 *
 * @param string $taskSuffix
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, setTaskSuffix){

	zval *task_suffix;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &task_suffix) == FAILURE) {
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_handlerSuffix"), task_suffix TSRMLS_CC);
	
}

/**
 * Sets the default task name
 *
 * @param string $taskName
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, setDefaultTask){

	zval *task_name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &task_name) == FAILURE) {
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_defaultHandler"), task_name TSRMLS_CC);
	
}

/**
 * Sets the task name to be dispatched
 *
 * @param string $taskName
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, setTaskName){

	zval *task_name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &task_name) == FAILURE) {
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_handlerName"), task_name TSRMLS_CC);
	
}

/**
 * Gets last dispatched task name
 *
 * @return string
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, getTaskName){

	zval *task_name;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(task_name);
	phalcon_read_property(&task_name, this_ptr, SL("_handlerName"), PH_NOISY_CC);
	
	RETURN_CCTOR(task_name);
}

/**
 * Throws an internal exception
 *
 * @param string $message
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, _throwDispatchException){

	zval *message;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &message) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_THROW_EXCEPTION_ZVAL(phalcon_cli_dispatcher_exception_ce, message);
	return;
}

/**
 * Returns the lastest dispatched controller
 *
 * @return Phalcon\CLI\Task
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, getLastTask){

	zval *last_controller;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(last_controller);
	phalcon_read_property(&last_controller, this_ptr, SL("_lastHandler"), PH_NOISY_CC);
	
	RETURN_CCTOR(last_controller);
}

/**
 * Returns the active task in the dispatcher
 *
 * @return Phalcon\CLI\Task
 */
PHP_METHOD(Phalcon_CLI_Dispatcher, getActiveTask){

	zval *task;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(task);
	phalcon_read_property(&task, this_ptr, SL("_activeHandler"), PH_NOISY_CC);
	
	RETURN_CCTOR(task);
}
