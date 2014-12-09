<?php
/**
 * @file
 * Disables, uninstalls and reinstalls a module.
 */
/**
 * Command callback.
 */
function drush_kc_flush() {
  $commands[] = array(
    'command' => 'updatedb',
    'options' => array('yes' => TRUE),
  );
  $commands[] = array(
    'command' => 'cache-clear',
    'arguments' => array('drush'),
  );
  $commands[] = array(
    'command' => 'features-revert-all',
    'options' => array('yes' => TRUE),
  );
  $commands[] = array(
    'command' => 'cache-clear',
    'arguments' => array('all'),
  );

  // Pass the drushrc file through to drush_invoke_process
  $default_options = array();
  if ($config = drush_get_option('config-file')) {
    $default_options['config'] = $config;
  }

  drush_shell_exec('git pull');
  foreach (drush_shell_exec_output() as $msg) {
    drush_print($msg);
  }

  foreach ($commands as $command) {
    $command += array('alias' => '@self', 'arguments' => array(), 'options' => array());
    $command['options'] += $default_options;

    drush_invoke_process($command['alias'], $command['command'], $command['arguments'], $command['options']);
    if (drush_get_error() != DRUSH_SUCCESS) {
      return drush_set_error('FLUSH_FAILED', dt('Flush failed on drush @command.', array('@command' => $command['command'])));
    }
  }

  // Success!
  drush_log(dt('Flush completed.'), 'success');
}
