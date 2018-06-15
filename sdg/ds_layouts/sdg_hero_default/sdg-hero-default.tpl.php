<?php
/**
 * @file
 *
 * Hero default.
 */
?>
<div class="hero hero--default no-constraints" >

  <div class="hero__image js-img-to-bg">
     <?php print $image; ?>
  </div>

  <div class="hero__content-outer constraints">
    <div class="hero__content-inner">
      <?php print $main_content; ?>
    </div>
  </div>

</div>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
