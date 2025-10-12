from zarinpal.exception import ZARINPAL_ERRORS, PaymentException


def test_error_mapping_exists():
    assert -30 in ZARINPAL_ERRORS
    assert issubclass(ZARINPAL_ERRORS[-30], PaymentException)
