<?php
/**
 * @file
 * Toolbox full of random tools compiled by Chris (KeyboardCowboy)
 */
/**
 * Implements hook_drush_command().
 */
function kc_drush_command() {
  $items['field-db-delete'] = array(
    'description' => 'Fix an issue where features can\'t create a field because it already exists by deleting the existing instances.',
    'arguments' => array(
      'field-name' => 'The name of the field to delete.',
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush field-db-delete field_project_title' => 'Delete field_project_title data and revision tables.',
    ),
    'aliases' => array('fdd'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  $items['reset'] = array(
    'description' => 'Batch command to run DB updates, revert features, clear caches.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  $items['sync-to-local'] = array(
    'description' => 'Sync a DB and run the necessary commands to prep a local environment.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'source-alias' => 'The source alias to fetch the DB from.',
    ),
    'required-arguments' => TRUE,
    'aliases' => array('stl'),
  );

  $items['site-on'] = array(
    'description' => 'Take a site out of maintenance mode and clear the cache.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('on'),
  );
  $items['site-off'] = array(
    'description' => 'Put a site into maintenance mode and clear the cache.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('off'),
  );

  $items['rerun-update'] = array(
    'description' => 'Rerun the latest update for a module.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'module' => 'The module to rerun.',
    ),
    'required-arguments' => TRUE,
  );

  $items['compare-schema'] = array(
    'description' => 'Compare the modules enabled and their versions between two sites.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'site-1' => 'A site alias.',
      'site-2' => 'Another site alias.',
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'status' => 'Filter by module status. (enabled or disabled)',
      'diff' => 'Only return modules where the schema differs between sites.',
    ),
    'examples' => array(
      'drush compare-schema @site.dev @site.stage' => 'Show the differences between the modules enabled and their versions.',
    ),
    'aliases' => array('compsch'),
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array('name' => 'Module', 'a1' => 'Alias 1', 'a2' => 'Alias 2'),
      'output-data-type' => 'format-table',
    ),
  );

  return $items;
}
