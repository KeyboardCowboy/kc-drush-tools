<?php
/**
 * @file
 * Disables, uninstalls and reinstalls a module.
 */
/**
 * Command callback.
 */
function drush_kc_pm_reinstall($mod) {
  if (drush_pm_disable($mod) !== FALSE) {
    if (drush_pm_uninstall($mod) !== FALSE) {
      drush_pm_enable_validate($mod);
      drush_pm_enable($mod);
    }
  }
}
