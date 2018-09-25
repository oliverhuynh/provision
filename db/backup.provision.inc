<?php

function drush_db_pre_provision_backup() {
  d()->service('db')->generate_dump();
  if (drush_get_option('force', false)) {
    drush_log("clearing error");
    drush_set_context('DRUSH_ERROR_CODE', DRUSH_SUCCESS);
  }
}

function drush_db_pre_provision_backup_rollback() {
  provision_file()->unlink(d()->site_path . '/database.sql')
    ->succeed('Deleted mysql dump from sites directory')
    ->fail('Could not delete mysql dump from sites directory');
}

function drush_db_post_provision_backup() {
  drush_db_pre_provision_backup_rollback();
}

