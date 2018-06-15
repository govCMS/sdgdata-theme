<?php
/**
 * @file
 * Layout for a goal teaser.
 *
 * This is specifically for use with a Goal taxonomy term and is complimented
 * by sdg_preprocess_taxonomy_term(). Using with another entity type/bundle
 * will cause you problems.
 */

/**
 * DS Implementation for goal teaser.
 */
function ds_sdg_goal_teaser() {
  return array(
    'label' => t('SDG: Goal Teaser'),
    'category' => t('SDG Custom'),
    'theme' => 'sdg_goal_teaser',
    'regions' => array(
      'front' => t('Front'),
      'back' => t('Back'),
      'visually_hidden' => t('Visually Hidden'),
    ),
    'css' => FALSE,
    'image' => FALSE,
  );
}
