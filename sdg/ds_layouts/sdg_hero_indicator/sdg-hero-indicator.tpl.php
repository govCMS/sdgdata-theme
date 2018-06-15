<?php
/**
 * @file
 *
 * Hero indicator.
 */
?>
<div class="hero hero--indicator" >

  <div class="hero__image js-img-to-bg">
     <?php print $image; ?>
  </div>

  <div class="hero__content">

    <div class="hero__text">
      <?php print $main_content; ?>
    </div>

    <div class="hero__goal">
      <?php print $goal; ?>
    </div>

  </div>

</div>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>

