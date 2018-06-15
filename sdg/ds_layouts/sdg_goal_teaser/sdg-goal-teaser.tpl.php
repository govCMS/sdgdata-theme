<?php
/**
 * @file
 *
 * Goal taxonomy teaser template.
 */
?>
<a href="<?php print $term_url ?>" class="goal-teaser goal--<?php print $machine_name; ?>--background" title="Click to learn more about <?php print $goal_name ?>">

  <span class="goal-teaser__hidden element-hidden">
     <?php print $visually_hidden; ?>
  </span>

  <span class="goal-teaser__front">
    <?php print $front; ?>
  </span>

  <span class="goal-teaser__back">
    <?php print $back; ?>
  </span>

</a>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>

