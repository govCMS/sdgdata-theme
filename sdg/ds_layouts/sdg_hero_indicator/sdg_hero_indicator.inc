<?php
/**
 * @file
 * Layout for a hero large.
 */

/**
 * DS Implementation for hero indicator.
 */
function ds_sdg_hero_indicator() {
  return array(
    'label' => t('SDG: Hero Indicator'),
    'category' => t('SDG Custom'),
    'theme' => 'sdg_hero_indicator',
    'regions' => array(
      'image' => t('Image'),
      'main_content' => t('Content'),
      'goal' => t('Goal'),
    ),
    'css' => FALSE,
    'image' => FALSE,
  );
}
