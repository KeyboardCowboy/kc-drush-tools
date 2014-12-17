<?php
/**
 * Command callback.
 */
function drush_kc_site_off() {
  $commands[] = array(
    'command' => 'variable_set',
    'arguments' => array('maintenance_mode', 1),
    'options' => array('exact'),
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

  foreach ($commands as $command) {
    $command += array('alias' => '@self', 'arguments' => array(), 'options' => array());
    $command['options'] += $default_options;

    drush_invoke_process($command['alias'], $command['command'], $command['arguments'], $command['options']);
    if (drush_get_error() != DRUSH_SUCCESS) {
      return drush_set_error('FLUSH_FAILED', dt('Failure on drush @command.', array('@command' => $command['command'])));
    }
  }

  // Success!
  drush_log(dt('Site is offline.'), 'success');
}
