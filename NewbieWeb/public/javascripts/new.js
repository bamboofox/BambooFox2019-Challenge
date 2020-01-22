$(document).ready(function() {
  $('#alert').hide();
  $('#submit').on('click', function(e) {
    e.preventDefault();
    $.ajax({
      url: '/new',
      type: 'POST',
      data: {
        file: $('#file').val(),
        code: $('#code').val(),
      },
      success: function(res) {
        console.log(res);
        if (!res.success) {
          showError(res.message);
        } else {
          showSuccess('Success! Redirecting...');
          setTimeout(() => {
            window.location.href = location.pathname + '?op=view&file=' +
              encodeURIComponent($('#file').val());
          }, 1000);
        }
      },
      fail: function() {
        showError('Unknown error');
      },
    });
  });
});

function showError(msg) {
  $('#message').text(msg);
  $('#alert').removeClass('alert-success').addClass('alert-danger').show();
}

function showSuccess(msg) {
  $('#message').text(msg);
  $('#alert').removeClass('alert-danger').addClass('alert-success').show();
}
