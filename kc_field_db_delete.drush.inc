<?php
/**
 * @file
 * Field Database Delete
 */
/**
 * Command callback validate.
 */
function drush_kc_field_db_delete_validate($fieldname) {
  $args = array('@name' => $fieldname);

  // Verify the field exists
  if (!db_table_exists("field_data_{$fieldname}")) {
    return drush_set_error('no-table', dt('Field @name does not appear to be a valid field. Missing data table.', $args));
  }
}

/**
 * Command callback.
 */
function drush_kc_field_db_delete($fieldname) {
  $args = array('@name' => $fieldname);

  // Confirm before deleting.
  if (!drush_confirm(dt('This will obliterate the field @name and all its data. Continue?', $args))) {
    drush_print(dt('Cancelled.'));
    return;
  }

  // Mark the field as deleted and let other modules first invoke their hooks.
  field_delete_field($fieldname);
  field_purge_batch(100);
  drush_log(dt("Purged field data."), 'success');

  // Delete data and revision tables.
  if (db_drop_table("field_data_{$fieldname}")) {
    drush_log(dt("Dropped table field_data_@name", $args), 'success');
  }

  if (db_drop_table("field_revision_{$fieldname}")) {
    drush_log(dt("Dropped table field_revision_@name", $args), 'success');
  }

  // Delete records from config and instance tables
  db_delete('field_config')->condition('field_name', $fieldname)->execute();
  db_delete('field_config_instance')->condition('field_name', $fieldname)->execute();
  drush_log(dt("Delete confif references."), 'success');
}
