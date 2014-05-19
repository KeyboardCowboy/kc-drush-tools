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
    'aliases' => array('kc-fdd'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}